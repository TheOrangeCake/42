package com.example.regular_user_service.services;

import com.example.regular_user_service.dto.EnvVariables;
import lombok.Getter;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;
import com.example.regular_user_service.exception.DeleteDefaultException;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.Arrays;
import java.util.UUID;

@Getter
@RequiredArgsConstructor
@Service
public class FileUploadService {
	private final EnvVariables envVariables;

	public String uploadImage(String userId, MultipartFile image, String fileExtension) throws IOException {
		if (userId == null || userId.isEmpty() || image == null || image.isEmpty() || fileExtension == null || fileExtension.isEmpty()) {
			throw new IllegalArgumentException("User ID, image, and file extension cannot be null or empty");
		}
		String uploadDir = envVariables.getUploadDir();
		if (uploadDir.isEmpty())
			throw new RuntimeException("No upload location specified");
		Path uploadPath = Paths.get(uploadDir).toAbsolutePath().normalize();
		if(!Files.exists(uploadPath)) {
			Files.createDirectories(uploadPath);
		}
		String fileName = userId + UUID.randomUUID() + fileExtension;
		Files.copy(image.getInputStream(), uploadPath.resolve(fileName), StandardCopyOption.REPLACE_EXISTING);
		return fileName;
	}

	public void deleteImage(String imageName) throws IOException {
		Path path = Paths.get(envVariables.getUploadDir());
		if (imageName == null
				|| imageName.isEmpty()
				|| imageName.equals(envVariables.getDefaultBanner())
				|| imageName.equals(envVariables.getDefaultAvatar()))
			throw new DeleteDefaultException("No image specified or can not delete default image");
		Path imagePath = path.resolve(imageName).normalize();
		if (!imagePath.startsWith(path.toAbsolutePath())) {
			throw new SecurityException("No");
		}
		Files.deleteIfExists(imagePath);
	}

	public boolean isImage(MultipartFile file) {
		if (file == null || file.isEmpty()) {
			return false;
		}
		String[] allowedType = {"image/gif", "image/jpeg", "image/png", "image/webp"};
		String contentType = file.getContentType();
		if (contentType == null || !contentType.startsWith("image/")) {
			return false;
		}
		if (Arrays.stream(allowedType).noneMatch(s -> s.equals(contentType))) {
			return false;
		}
		String fileName = file.getOriginalFilename();
		if (fileName == null) {
			return false;
		}
		try {
			BufferedImage image = ImageIO.read(file.getInputStream());
			if (image == null)
				return false;
		} catch(IOException e) {
			return false;
		}
		return true;
	}

	public String getFileExtension(MultipartFile file) {
		if (file == null || file.isEmpty()) {
			return null;
		}
		String[] allowedExtension = {".gif", ".jpeg", ".jpg", ".png", ".webp"};
		String fileName = file.getOriginalFilename();
		if (fileName == null || !fileName.contains(".")) {
			return null;
		}
		String extension = fileName.substring(fileName.lastIndexOf(".")).toLowerCase();
		if (Arrays.stream(allowedExtension).noneMatch(s -> s.equals(extension))) {
			return null;
		}
		return extension;
	}
}