package com.example.regular_user_service.dto;

import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;

public record UpdateDto(
		@NotBlank(message="Email can not be blank")
		@Email(regexp = ".+@.+\\..+")
		String email,
		String first_name,
		String last_name,
		boolean double_authentication,
		@NotBlank(message="Password can not be blank")
		String confirm_password
) {
}