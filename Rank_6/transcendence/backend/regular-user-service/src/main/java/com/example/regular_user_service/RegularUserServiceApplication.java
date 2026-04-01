package com.example.regular_user_service;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.security.autoconfigure.UserDetailsServiceAutoConfiguration;

@SpringBootApplication(exclude= {UserDetailsServiceAutoConfiguration.class})
public class RegularUserServiceApplication {

	public static void main(String[] args) {
		SpringApplication.run(RegularUserServiceApplication.class, args);
	}

}
