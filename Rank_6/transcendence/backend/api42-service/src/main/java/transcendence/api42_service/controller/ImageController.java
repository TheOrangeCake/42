package transcendence.api42_service.controller;


import lombok.AllArgsConstructor;
import org.springframework.core.io.Resource;
import org.springframework.core.io.UrlResource;
import org.springframework.http.InvalidMediaTypeException;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import transcendence.api42_service.dto.EnvVariables;
import transcendence.api42_service.exception.WrongExtensionException;

import java.net.MalformedURLException;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.springframework.http.MediaType.parseMediaType;

@AllArgsConstructor
@RestController
public class ImageController {
	private final EnvVariables envVariables;

	@GetMapping("/images42/{fileName}")
	public ResponseEntity<?> getImage(@PathVariable String fileName) {
		if (fileName == null || fileName.trim().isEmpty()) {
			return ResponseEntity.badRequest().body("File name cannot be null or empty");
		}
		try {
			Path imagePath = Paths.get(envVariables.getUploadDir()).resolve(fileName).normalize();
			if (!imagePath.startsWith(Paths.get(envVariables.getUploadDir()).toAbsolutePath())) {
				return ResponseEntity.status(403).body("Access denied");
			}
			Resource resource = new UrlResource(imagePath.toUri());
			if (!resource.exists() || !resource.isReadable()) {
				return ResponseEntity.status(404).body("Image not found");
			}
			return ResponseEntity.ok().contentType(getMediaType(fileName)).body(resource);
		} catch(InvalidPathException | MalformedURLException e) {
			return ResponseEntity.status(404).body("Image not found");
		} catch(WrongExtensionException | InvalidMediaTypeException e) {
			return ResponseEntity.status(400).body("Bad file extension");
		} catch (Exception e) {
			return ResponseEntity.internalServerError().body("Internal server error");
		}
    }

	private MediaType getMediaType(String fileName) {
		if (fileName == null || !fileName.contains(".")) {
			throw new WrongExtensionException();
		}
		String extension = fileName.substring(fileName.lastIndexOf(".")).toLowerCase();
		return switch (extension) {
			case (".gif") -> MediaType.IMAGE_GIF;
			case (".jpg"), (".jpeg") -> MediaType.IMAGE_JPEG;
			case (".png") -> MediaType.IMAGE_PNG;
			case (".webp") -> parseMediaType("image/webp");
			default -> throw new WrongExtensionException();
		};
	}
}