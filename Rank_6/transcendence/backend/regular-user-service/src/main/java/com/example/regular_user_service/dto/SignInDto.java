package com.example.regular_user_service.dto;

import jakarta.validation.constraints.NotBlank;

public record SignInDto(
		@NotBlank(message="Login can not be blank")
		String login,
		@NotBlank(message="Password can not be blank")
		String password
) {
}