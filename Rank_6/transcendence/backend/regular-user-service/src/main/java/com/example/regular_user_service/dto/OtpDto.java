package com.example.regular_user_service.dto;

import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;

public record OtpDto(
        @NotBlank(message="Email can not be blank")
        @Email(regexp = ".+@.+\\..+")
        String email,
        @NotNull(message = "Otp can not be blank")
        Integer otp
) {
}