package com.transcendence.auth.web;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.security.Keys;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.CookieValue;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.crypto.SecretKey;
import java.nio.charset.StandardCharsets;
import java.util.Map;

@RestController
public class JwtDebugController {

    private final SecretKey key;

    public JwtDebugController(@Value("${app.jwt.secret}") String secret) {
        this.key = Keys.hmacShaKeyFor(secret.getBytes(StandardCharsets.UTF_8));
    }

    @GetMapping(value = "/debug/jwt", produces = MediaType.APPLICATION_JSON_VALUE)
    public Map<String, Object> debugJwt(
            @CookieValue(name = "access_token", required = false) String token
    ) {
        if (token == null || token.isBlank()) {
            return Map.of("error", "no_access_token_cookie");
        }

        Claims claims = Jwts.parser()
                .verifyWith(key)
                .build()
                .parseSignedClaims(token)
                .getPayload();

        return Map.of(
                "header", Map.of("alg", "HS256", "typ", "JWT"),
                "claims", claims
        );
    }
}
