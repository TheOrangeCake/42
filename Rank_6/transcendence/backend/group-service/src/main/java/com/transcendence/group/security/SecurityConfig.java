package com.transcendence.group.security;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.web.SecurityFilterChain;

@Configuration
public class SecurityConfig {

  private final CookieBearerTokenResolver cookieBearerTokenResolver;

  public SecurityConfig(CookieBearerTokenResolver cookieBearerTokenResolver) {
    this.cookieBearerTokenResolver = cookieBearerTokenResolver;
  }

  @Bean
  SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
    http
      .csrf(csrf -> csrf.disable())
      .authorizeHttpRequests(auth -> auth
        .requestMatchers("/public/**", "/actuator/**").permitAll()
        .anyRequest().authenticated()
      )
      .oauth2ResourceServer(oauth2 -> oauth2
        .bearerTokenResolver(cookieBearerTokenResolver) 
        .jwt(jwt -> {})
      );

    return http.build();
  }
}
