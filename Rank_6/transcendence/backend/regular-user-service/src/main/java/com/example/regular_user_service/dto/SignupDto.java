package com.example.regular_user_service.dto;

import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Pattern;

public record SignupDto(
		@NotBlank(message="Username can not be blank")
		@Pattern(
				regexp = "^[A-Za-z0-9_]+( [A-Za-z0-9_]+)*$",
				message = "Username may only contain letters, numbers, spaces, and underscores. " +
						"No leading or trailing whitespaces.")
		String username,
		@NotBlank(message="Email can not be blank")
		@Email(regexp = ".+@.+\\..+")
		String email,
		@NotBlank(message="Password can not be blank")
		@Pattern(
				regexp = "^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)\\S.{6,}\\S$",
				message = "Password must be at least 8 characters long, " +
						"include 1 uppercase, 1 lowercase, 1 number. No leading or trailing whitespaces.")
		String password
) {
}