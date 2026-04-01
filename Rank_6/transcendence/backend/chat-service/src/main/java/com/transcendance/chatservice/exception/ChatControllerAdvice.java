package com.transcendance.chatservice.exception;

import io.jsonwebtoken.JwtException;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.server.ResponseStatusException;

import java.time.LocalDateTime;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

/**
 * Centralized exception handler for chat-service REST endpoints.
 * Note: WebSocket errors are handled differently via AuthChannelInterceptor.
 */
@ControllerAdvice
public class ChatControllerAdvice {

    /**
     * Handle JWT validation errors (from JJWT library)
     */
    @ExceptionHandler(JwtException.class)
    public ResponseEntity<Map<String, Object>> handleJwtException(JwtException ex) {
        Map<String, Object> response = new HashMap<>();
        response.put("error", "JWT_VALIDATION_FAILED");
        response.put("message", "Invalid or expired token");
        response.put("details", ex.getMessage());
        response.put("timestamp", LocalDateTime.now());
        return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body(response);
    }

    /**
     * Handle custom JWT exceptions
     */
    @ExceptionHandler(InvalidJwtException.class)
    public ResponseEntity<Map<String, Object>> handleInvalidJwtException(InvalidJwtException ex) {
        Map<String, Object> response = new HashMap<>();
        response.put("error", "INVALID_JWT");
        response.put("message", ex.getMessage());
        response.put("timestamp", LocalDateTime.now());
        return ResponseEntity.status(HttpStatus.UNAUTHORIZED).body(response);
    }

    /**
     * Handle invalid message format or invalid arguments
     */
    @ExceptionHandler(IllegalArgumentException.class)
    public ResponseEntity<Map<String, Object>> handleIllegalArgumentException(IllegalArgumentException ex) {
        Map<String, Object> response = new HashMap<>();
        response.put("error", "INVALID_ARGUMENT");
        response.put("message", ex.getMessage());
        response.put("timestamp", LocalDateTime.now());
        return ResponseEntity.status(HttpStatus.BAD_REQUEST).body(response);
    }

    /**
     * Handle Spring ResponseStatusException (thrown by endpoints)
     */
    @ExceptionHandler(ResponseStatusException.class)
    public ResponseEntity<Map<String, Object>> handleResponseStatusException(ResponseStatusException ex) {
        Map<String, Object> response = new HashMap<>();
        response.put("error", "REQUEST_FAILED");
        response.put("message", ex.getReason());
        response.put("timestamp", LocalDateTime.now());
        return ResponseEntity.status(ex.getStatusCode()).body(response);
    }

    /**
     * Generic handler for all other exceptions
     */
    @ExceptionHandler(Exception.class)
    public ResponseEntity<Map<String, Object>> handleGlobalException(Exception ex) {
        Map<String, Object> response = new HashMap<>();
        response.put("error", "INTERNAL_SERVER_ERROR");
        response.put("message", "An unexpected error occurred");
        response.put("details", ex.getMessage());
        response.put("timestamp", LocalDateTime.now());
        return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(response);
    }
}
