package com.example.regular_user_service.dto.mapper;

import com.example.regular_user_service.dto.UserDto;
import com.example.regular_user_service.entities.User;

public class UserMapper {
	public static UserDto mapToResponseDto(User user, String imageDomain) {
		return new UserDto(
				user.getId(),
				user.getUsername(),
				user.getEmail(),
				imageDomain + user.getCustomAvatarUrl(),
				imageDomain + user.getCustomBannerUrl(),
				user.getFirstName(),
				user.getLastName(),
				user.isDoubleAuth(),
				user.isActive()
		);
	}
}