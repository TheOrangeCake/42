package com.transcendence.group.security;

import java.nio.charset.StandardCharsets;

import javax.crypto.spec.SecretKeySpec;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.oauth2.jose.jws.MacAlgorithm;
import org.springframework.security.oauth2.jwt.JwtDecoder;
import org.springframework.security.oauth2.jwt.NimbusJwtDecoder;

@Configuration
public class JwtDecoderConfig {

  @Bean
  JwtDecoder jwtDecoder(@Value("${app.jwt.secret}") String secret) {
    var key = new SecretKeySpec(secret.getBytes(StandardCharsets.UTF_8), "HmacSHA512");
    return NimbusJwtDecoder
        .withSecretKey(key)
        .macAlgorithm(MacAlgorithm.HS512)
        .build();
  }
}
