package com.example.regular_user_service.exception;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.FieldError;
import org.springframework.web.server.ResponseStatusException;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

@ControllerAdvice
public class GlobalExceptionHandler {

	@ExceptionHandler(MethodArgumentNotValidException.class)
	public ResponseEntity<Map<String, String>> handleValidationExceptions(MethodArgumentNotValidException ex) {
		Map<String, String> errors = new HashMap<>();
		ex.getBindingResult().getAllErrors().forEach(error -> {
			String fieldName = ((FieldError) error).getField();
			String errorMessage = error.getDefaultMessage();
			errors.put(fieldName, errorMessage);
		});
		return ResponseEntity.badRequest().body(errors);
	}

	@ExceptionHandler(ResponseStatusException.class)
	public ResponseEntity<Map<String, String>> handleResponseStatusException(ResponseStatusException ex) {
		return ResponseEntity.status(ex.getStatusCode())
				.body(Collections.singletonMap("error", ex.getReason()));
	}

	@ExceptionHandler(BadTokenException.class)
	public ResponseEntity<Map<String, String>> handleBadTokenException(BadTokenException ex) {
		return ResponseEntity.status(HttpStatus.UNAUTHORIZED)
				.body(Collections.singletonMap("error", ex.getMessage()));
	}
}
