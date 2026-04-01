package com.example.regular_user_service.config;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;

@Data
@ConfigurationProperties(prefix = "spring.mail")
public class EmailConfig {

    private String username;
}