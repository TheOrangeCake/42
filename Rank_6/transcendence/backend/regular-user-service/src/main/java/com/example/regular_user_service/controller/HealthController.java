package com.example.regular_user_service.controller;

import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/v1/regular-user/health")
@AllArgsConstructor
public class HealthController {

	@GetMapping
	public ResponseEntity<String> healthCheck() {
		return ResponseEntity.ok("Healthy");
	}
}