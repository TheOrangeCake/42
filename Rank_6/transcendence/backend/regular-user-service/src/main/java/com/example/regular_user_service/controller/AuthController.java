package com.example.regular_user_service.controller;

import com.example.regular_user_service.dto.*;
import com.example.regular_user_service.dto.mapper.UserMapper;
import com.example.regular_user_service.entities.User;
import com.example.regular_user_service.exception.BadTokenException;
import com.example.regular_user_service.repositories.UserRepository;
import com.example.regular_user_service.services.EmailService;
import com.example.regular_user_service.services.JwtService;
import com.google.common.cache.LoadingCache;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.dao.DataIntegrityViolationException;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseCookie;
import org.springframework.http.ResponseEntity;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;

import java.util.Date;
import java.util.Random;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.logging.Logger;

@RequiredArgsConstructor
@RestController
@RequestMapping("/v1/regular-user/auth")
public class AuthController {
	private final UserRepository userRepository;
	private final PasswordEncoder passwordEncoder;
	private final JwtService jwtService;
	private final EnvVariables envVariables;
	private final Logger logger;
	private final LoadingCache<String, Integer> otpCache;
	private final EmailService emailService;

	@PostMapping("/signup")
	public ResponseEntity<?> createUser(@Valid @RequestBody SignupDto signupDto) {
		try {
			User newUser = new User();
			newUser.setUsername(signupDto.username().toLowerCase());
			newUser.setEmail(signupDto.email().toLowerCase());
			newUser.setPassword(passwordEncoder.encode(signupDto.password()));
			newUser.setCustomAvatarUrl(envVariables.getDefaultAvatar());
			newUser.setCustomBannerUrl(envVariables.getDefaultBanner());
			newUser.setDoubleAuth(false);
			newUser.setActive(true);
			newUser.setCreatedAt(new Date());
			userRepository.save(newUser);
			logger.info("A new user is created. User id: " + newUser.getId());
			UserDto createdUser = UserMapper.mapToResponseDto(newUser, envVariables.getImageDomain());
			return ResponseEntity.ok().body(createdUser);
		} catch (DataIntegrityViolationException e) {
			return ResponseEntity.status(HttpStatus.CONFLICT).body("Username or Email already existed");
		} catch (RuntimeException e) {
			logger.severe("User creation failed: " + e.getMessage());
			return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("Internal server error, user creation failed. " + e.getMessage());
		}
	}

	@PostMapping("/signin")
	public ResponseEntity<?> loginUser(@Valid @RequestBody SignInDto signInDto) {
		String login = signInDto.login().toLowerCase();
		User user = userRepository.findUserByEmailOrUsername(login, login)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.UNAUTHORIZED, "Wrong username, email or password"));
		if (!passwordEncoder.matches(signInDto.password(), user.getPassword())) {
			return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Wrong username, email or password");
		}
		Long userId = user.getId();
		user.setLoginAttempt(0);
		userRepository.save(user);
		if (user.isDoubleAuth()) {
			sendOtp(user);
			return ResponseEntity.accepted().body("2FA email sent to user. Call /v1/regular-user/auth/verify-otp with email and otp to login.");
		} else {
			logger.info("User " + userId + " logged in");
			return generateResponse(user, userId);
		}
	}

	private void sendOtp(User user) {
		otpCache.invalidate(user.getEmail());
		int otp = new Random().nextInt(900000) + 100000;
		otpCache.put(user.getEmail(), otp);
		CompletableFuture.supplyAsync(() -> {
			try {
				emailService.sendEmail(user.getEmail(), "2FA: Request to log in to your account", "One Time Password (valid 5 minutes): " + otp);
				return HttpStatus.OK;
			} catch (Exception e) {
				logger.severe("Failed to send OTP email to " + user.getEmail() + ": " + e.getMessage());
				return HttpStatus.INTERNAL_SERVER_ERROR;
			}
		}).thenAccept(status -> {
			if (status == HttpStatus.OK) {
				logger.info("2FA email sent to user " + user.getId());
			} else {
				logger.severe("Failed to send OTP email to " + user.getEmail());
			}
		});
	}

	@PostMapping("/verify-otp")
	public ResponseEntity<?> verifyOtp(@Valid @RequestBody OtpDto otpDto) {
		User user = userRepository.findUserByEmail(otpDto.email())
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.UNAUTHORIZED, "Email not existed."));
		long userId = user.getId();
		Integer storedOtp;
		try {
			storedOtp = otpCache.get(user.getEmail());
		} catch (ExecutionException e) {
			logger.severe("Failed to retrieve OTP from cache for email: " + user.getEmail() + ". Error: " + e.getMessage());
			return ResponseEntity.internalServerError().body("Something wrong with the server, please try again later.");
		}
		if (storedOtp.equals(otpDto.otp())) {
			otpCache.invalidate(user.getEmail());
			logger.info("User " + userId + " logged in");
			user.setLoginAttempt(0);
			userRepository.save(user);
			return generateResponse(user, userId);
		} else {
			int loginAttempts = user.getLoginAttempt();
			if (loginAttempts >= 5) {
				otpCache.invalidate(user.getEmail());
				return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Max 5 attempts reached.");
			}
			user.setLoginAttempt(loginAttempts + 1);
			userRepository.save(user);
			return ResponseEntity.badRequest().body("Invalid or expired OTP.");
		}
	}

	@GetMapping("/refresh-token")
	public ResponseEntity<?> refreshToken(HttpServletRequest request) {
		try {
			String currentRefreshToken = jwtService.extractRefreshToken(request);
			jwtService.validateJwtToken(currentRefreshToken, "refresh token");
			Long userId = Long.parseLong(jwtService.getUserId(currentRefreshToken, "refresh token"));
			User user = userRepository.findUserById(userId)
					.orElseThrow(() -> new BadTokenException("User not found"));
			jwtService.revokeToken(currentRefreshToken, "refresh token");

			try {
				String currentAccessToken = jwtService.extractAccessToken(request);
				jwtService.revokeToken(currentAccessToken, "access token");
			} catch (Exception ignored) {
				// No access token in header (e.g. new browser window) — skip revocation
			}

			logger.info("User " + userId + " has generated new refresh and access tokens");
			return generateResponse(user, userId);
		} catch (Exception e) {
			return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body("Invalid token: please sign in again");
		}
	}

	private ResponseEntity<UserDto> generateResponse(User user, Long userId) {
		String newAccessToken = jwtService.generateAccessToken(userId);
		String newRefreshToken = jwtService.generateRefreshToken(userId);
		ResponseCookie refreshTokenCookie = ResponseCookie.from("refreshToken", newRefreshToken)
				.httpOnly(true)
				.secure(true)
				.sameSite("Lax")
				.path("/")
				.maxAge(7 * 24 * 60 * 60)
				.build();
		return ResponseEntity.ok()
				.header(HttpHeaders.AUTHORIZATION, "Bearer " + newAccessToken)
				.header(HttpHeaders.SET_COOKIE, refreshTokenCookie.toString())
				.body(UserMapper.mapToResponseDto(user, envVariables.getImageDomain()));
	}
}
