package com.example.regular_user_service.dto;

import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Getter
@Component
public class EnvVariables {
	@Value("${regUser.default-banner}")
	private String defaultBanner;

	@Value("${regUser.default-avatar}")
	private String defaultAvatar;

	@Value("${regUser.image-domain}")
	private String imageDomain;

	@Value("${regUser.upload-location}")
	private String uploadDir;
}