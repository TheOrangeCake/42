package com.example.regular_user_service.controller;


import com.example.regular_user_service.dto.EnvVariables;
import com.example.regular_user_service.exception.WrongExtensionException;
import lombok.AllArgsConstructor;
import org.springframework.core.io.Resource;
import org.springframework.core.io.UrlResource;
import org.springframework.http.InvalidMediaTypeException;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import java.net.MalformedURLException;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.logging.Logger;

import static org.springframework.http.MediaType.parseMediaType;

@AllArgsConstructor
@RestController
public class ImageController {
	private final EnvVariables envVariables;
	private final Logger logger;

	@GetMapping("/images-regular/{fileName}")
	public ResponseEntity<?> getImage(@PathVariable String fileName) {
		if (fileName == null || fileName.trim().isEmpty()) {
			return ResponseEntity.badRequest().body("File name cannot be null or empty");
		}
		try {
			Path imagePath = Paths.get(envVariables.getUploadDir()).resolve(fileName).normalize();
			if (!imagePath.startsWith(Paths.get(envVariables.getUploadDir()).toAbsolutePath())) {
				logger.warning("Someone is trying to access files outside of upload directory");
				return ResponseEntity.status(403).body("No");
			}
			Resource resource = new UrlResource(imagePath.toUri());
			if (!resource.exists() || !resource.isReadable()) {
				return ResponseEntity.status(404).body("Image not found");
			}
			return ResponseEntity.ok().contentType(getMediaType(fileName)).body(resource);
		} catch(InvalidPathException | MalformedURLException e) {
			return ResponseEntity.status(404).body("Image not found");
		} catch(WrongExtensionException | InvalidMediaTypeException e) {
			return ResponseEntity.badRequest().body(e.getMessage());
		} catch (Exception e) {
			return ResponseEntity.internalServerError().body("Internal server error");
		}
	}

	private MediaType getMediaType(String fileName) {
		if (fileName == null || !fileName.contains(".")) {
			throw new WrongExtensionException("Bad file extension");
		}
		String extension = fileName.substring(fileName.lastIndexOf(".")).toLowerCase();
		return switch (extension) {
			case (".gif") -> MediaType.IMAGE_GIF;
			case (".jpg"), (".jpeg") -> MediaType.IMAGE_JPEG;
			case (".png") -> MediaType.IMAGE_PNG;
			case (".webp") -> parseMediaType("image/webp");
			default -> throw new WrongExtensionException("Bad file extension");
		};
	}
}