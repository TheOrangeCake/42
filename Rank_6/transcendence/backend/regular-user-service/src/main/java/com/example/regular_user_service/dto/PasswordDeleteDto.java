package com.example.regular_user_service.dto;

import jakarta.validation.constraints.AssertTrue;
import jakarta.validation.constraints.NotBlank;

public record PasswordDeleteDto(
	@NotBlank(message="Password can not be blank")
	String confirm_password,
	@AssertTrue(message = "Deletion not confirmed")
	boolean confirm_deletion
) {
}