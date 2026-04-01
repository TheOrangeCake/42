package com.example.regular_user_service.controller;

import com.example.regular_user_service.dto.EnvVariables;
import com.example.regular_user_service.dto.PasswordDeleteDto;
import com.example.regular_user_service.dto.UpdateDto;
import com.example.regular_user_service.dto.UserDto;
import com.example.regular_user_service.dto.mapper.UserMapper;
import com.example.regular_user_service.entities.User;
import com.example.regular_user_service.exception.BadTokenException;
import com.example.regular_user_service.exception.DeleteDefaultException;
import com.example.regular_user_service.repositories.UserRepository;
import com.example.regular_user_service.services.FileUploadService;
import com.example.regular_user_service.services.JwtService;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.validation.Valid;
import jakarta.validation.constraints.NotBlank;
import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseCookie;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.server.ResponseStatusException;

import java.io.IOException;
import java.util.Map;
import java.util.logging.Logger;

@RequiredArgsConstructor
@RestController
@RequestMapping("/v1/regular-user/user")
public class UserController {
	private final UserRepository userRepository;
	private final EnvVariables envVariables;
	private final PasswordEncoder passwordEncoder;
	private final FileUploadService fileUploadService;
	private final JwtService jwtService;
	private final Logger logger;

	@GetMapping("/profile/{id}")
	public ResponseEntity<?> getUser(@PathVariable Long id) {
		User user = userRepository.findUserById(id)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "User not found"));
		return ResponseEntity.ok(UserMapper.mapToResponseDto(user, envVariables.getImageDomain()));
	}

	@GetMapping("/profile")
	public ResponseEntity<UserDto> getMyProfile() {
		Long userId = getUserId();
		User user = userRepository.findUserById(userId)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "User not found"));
		return ResponseEntity.ok(UserMapper.mapToResponseDto(user, envVariables.getImageDomain()));
	}

	@PutMapping("/profile")
	public ResponseEntity<?> updateProfile(@Valid @RequestBody UpdateDto info) {
		Long userId = getUserId();
		User user = userRepository.findUserById(userId)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "User not found"));
		if (!passwordEncoder.matches(info.confirm_password(), user.getPassword())) {
			return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Wrong password");
		}
		if (!info.email().equals(user.getEmail()) && userRepository.existsByEmail(info.email())) {
			return ResponseEntity.badRequest().body("Email is already used");
		} else if (!info.email().equals(user.getEmail())) {
			user.setEmail(info.email());
		}
		if (info.first_name() != null) {
			user.setFirstName(info.first_name());
		}
		if (info.last_name() != null) {
			user.setLastName(info.last_name());
		}
		user.setDoubleAuth(info.double_authentication());
		userRepository.save(user);
		return ResponseEntity.ok(UserMapper.mapToResponseDto(user, envVariables.getImageDomain()));
	}

	@DeleteMapping("/profile")
	public ResponseEntity<String> deleteMyProfile(@Valid @RequestBody PasswordDeleteDto password) {
		Long userId = getUserId();
		User user = userRepository.findUserById(userId).orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "User not found"));
		if (!passwordEncoder.matches(password.confirm_password(), user.getPassword())) {
			return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Wrong password");
		}
		if (password.confirm_deletion()) {
			try {
				fileUploadService.deleteImage(user.getCustomAvatarUrl());
			} catch(DeleteDefaultException e) {
			} catch(Exception e) {
				logger.severe("Fail to delete custom avatar in account " + user.getId() + " desactivation: " + e.getMessage());
			}
			try {
				fileUploadService.deleteImage(user.getCustomBannerUrl());
			} catch(DeleteDefaultException e) {
			} catch(Exception e) {
				logger.severe("Fail to delete custom banner in account " + user.getId() + " desactivation: " + e.getMessage());
			}
			user.setCustomAvatarUrl(envVariables.getDefaultAvatar());
			user.setCustomBannerUrl(envVariables.getDefaultBanner());
			user.setFirstName(null);
			user.setLastName(null);
			user.setActive(false);
			userRepository.save(user);
			return ResponseEntity.ok("User is deactived");
		}
		return ResponseEntity.badRequest().body("Account deactivation not confirmed");
	}

	private Long getUserId() {
		Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
		if (authentication == null || authentication.getPrincipal() == null) {
			throw new BadTokenException("Invalid access token: User Id not found");
		}
		return Long.parseLong(authentication.getPrincipal().toString());
	}

	@PatchMapping("/profile/avatar")
	public ResponseEntity<?> modifyAvatar(@RequestParam("avatar") MultipartFile avatar,
	                                      HttpServletRequest request,
	                                      @RequestParam @NotBlank(message = "Password can not be blank") String confirm_password) {
		Long userId = getUserId();
		User user = this.userRepository.findById(userId)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "User not found"));
		if (!passwordEncoder.matches(confirm_password, user.getPassword())) {
			return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Wrong password");
		}
		return modifyImage(user, avatar, request, "avatar");
	}

	@PatchMapping("/profile/banner")
	public ResponseEntity<?> modifyBanner(@RequestParam("banner") MultipartFile banner,
	                                      HttpServletRequest request,
	                                      @RequestParam @NotBlank(message = "Password can not be blank") String confirm_password) {
		Long userId = getUserId();
		User user = this.userRepository.findById(userId)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "User not found"));
		if (!passwordEncoder.matches(confirm_password, user.getPassword())) {
			return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Wrong password");
		}
		return modifyImage(user, banner, request, "banner");
	}

	private ResponseEntity<?> modifyImage(User user, MultipartFile image, HttpServletRequest request, String type) {
		if (!request.getContentType().startsWith("multipart/form-data")) {
			return ResponseEntity.badRequest().body("Request must be multipart/form-data");
		}
		if (image.isEmpty() || !fileUploadService.isImage(image)) {
			return ResponseEntity.badRequest().body("Invalid file or no Content-Type header");
		}
		String fileExtension = fileUploadService.getFileExtension(image);
		if (fileExtension == null) {
			return ResponseEntity.badRequest().body("Invalid file extension. Allowed: .gif, .jpg, .jpeg, .png, .webp");
		}
		try {
			String fileName = fileUploadService.uploadImage(user.getId().toString(), image, fileExtension);
			if (type.equals("avatar")) {
				if (!user.getCustomAvatarUrl().equals(envVariables.getDefaultAvatar())) {
					fileUploadService.deleteImage(user.getCustomAvatarUrl());
				}
				user.setCustomAvatarUrl(fileName);
			} else if (type.equals("banner")) {
				if (!user.getCustomBannerUrl().equals(envVariables.getDefaultBanner())) {
					fileUploadService.deleteImage(user.getCustomBannerUrl());
				}
				user.setCustomBannerUrl(fileName);
			} else {
				logger.severe("Fail to upload file, something went wrong in the server");
				return ResponseEntity.internalServerError().body("Fail to upload file, something went wrong in the server.");
			}
			userRepository.save(user);
			return ResponseEntity.ok(UserMapper.mapToResponseDto(user, envVariables.getImageDomain()));
		} catch (IOException | RuntimeException e) {
			logger.severe("Fail to upload file. " + e.getMessage());
			return ResponseEntity.internalServerError().body("Fail to upload file. Something went wrong in the server.");
		}
	}

	@DeleteMapping("/profile/avatar")
	public ResponseEntity<?> deleteAvatar(@RequestParam @NotBlank(message = "Password can not be blank") String confirm_password) {
		Long userId = getUserId();
		User user = this.userRepository.findById(userId)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "User not found"));
		if (!passwordEncoder.matches(confirm_password, user.getPassword())) {
			return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Wrong password");
		}
		return deleteImage(user, "avatar");
	}

	@DeleteMapping("/profile/banner")
	public ResponseEntity<?> deleteBanner(@RequestParam @NotBlank(message = "Password can not be blank") String confirmPassword) {
		Long userId = getUserId();
		User user = this.userRepository.findById(userId)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "User not found"));
		if (!passwordEncoder.matches(confirmPassword, user.getPassword())) {
			return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Wrong password");
		}
		return deleteImage(user, "banner");
	}

	private ResponseEntity<?> deleteImage(User user, String type) {
		try {
			if (type.equals("banner")) {
				fileUploadService.deleteImage(user.getCustomBannerUrl());
				user.setCustomBannerUrl(envVariables.getDefaultBanner());
			} else if (type.equals("avatar")) {
				fileUploadService.deleteImage(user.getCustomAvatarUrl());
				user.setCustomAvatarUrl(envVariables.getDefaultAvatar());
			} else {
				logger.severe("Image deletion failed. Something went wrong in the server");
				return ResponseEntity.internalServerError().body("Image deletion failed. Something went wrong in the server");
			}
			userRepository.save(user);
			return ResponseEntity.ok(UserMapper.mapToResponseDto(user, envVariables.getImageDomain()));
		} catch(IOException e) {
			logger.severe("Image deletion failed. Error: " + e.getMessage());
			return ResponseEntity.internalServerError().body("Image deletion failed. Something went wrong in the server");
		} catch(SecurityException e) {
			return ResponseEntity.status(403).body(e.getMessage());
		} catch(DeleteDefaultException e) {
			return ResponseEntity.badRequest().body(e.getMessage());
		}
	}

	@GetMapping("/signout")
	public ResponseEntity<?> logoutUser(HttpServletRequest request) {
		try {
			String currentRefreshToken = jwtService.extractRefreshToken(request);
			String currentAccessToken = jwtService.extractAccessToken(request);
			jwtService.validateJwtToken(currentAccessToken, "access token");
			jwtService.revokeToken(currentAccessToken, "access token");
			jwtService.validateJwtToken(currentRefreshToken, "refresh token");
			long userId = Long.parseLong(jwtService.getUserId(currentRefreshToken, "refresh token"));
			jwtService.revokeToken(currentRefreshToken, "refresh token");
			ResponseCookie refreshTokenCookie = ResponseCookie.from("refreshToken", "")
					.httpOnly(true)
					.secure(true)
					.sameSite("Lax")
					.path("/")
					.maxAge(0)
					.build();
			logger.info("User " + userId + " logged out");
			return ResponseEntity.ok()
					.header(HttpHeaders.SET_COOKIE, refreshTokenCookie.toString())
					.body(Map.of("message", "Sign out successfully"));
		} catch (BadTokenException e) {
			return ResponseEntity.badRequest().body("{\"error\": \"" + e.getMessage() + "\"}");
		}
	}
}
