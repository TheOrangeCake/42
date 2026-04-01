package com.example.regular_user_service.dto;

public record UserDto(
	Long id,
	String username,
	String email,
	String custom_avatar_url,
	String custom_banner_url,
	String first_name,
	String last_name,
	boolean double_authentication,
	boolean active
) {
}