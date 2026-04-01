package com.transcendence.auth.security;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.security.Keys;

import java.nio.charset.StandardCharsets;
import java.time.Instant;
import java.util.Date;
import java.util.Map;
import java.util.HashMap;

import javax.crypto.SecretKey;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

@Service
public class JwtService {

    private final SecretKey key;
    private final long ttlMinutes;

    public JwtService(
            @Value("${JWT_SECRET}") String secret,
            @Value("${app.jwt.ttl-minutes:120}") long ttlMinutes) {
        this.key = Keys.hmacShaKeyFor(secret.getBytes(StandardCharsets.UTF_8));
        this.ttlMinutes = ttlMinutes;
    }
     
    public String issue(String login, String email, long ttlMinutesOverride) {
        Map<String, Object> claims = new HashMap<>();
        claims.put("email", email);

        Instant now = Instant.now();
        Instant exp = now.plusSeconds(ttlMinutesOverride * 60);

        return Jwts.builder()
                .subject(login)
                .issuedAt(Date.from(now))
                .expiration(Date.from(exp))
                .claims(claims)
                .signWith(key)
                .compact();
    }

    public String createToken(String subjectLogin, Map<String, Object> claims) {
        Instant now = Instant.now();
        Instant exp = now.plusSeconds(ttlMinutes * 60);

        return Jwts.builder()
                .subject(subjectLogin)
                .issuedAt(Date.from(now))
                .expiration(Date.from(exp))
                .claims(claims)
                .signWith(key)
                .compact();
    }

    public Claims parse(String token) {
        return (Claims) Jwts.parser()
                .verifyWith(key)
                .build()
                .parse(token)
                .getPayload();
    }
}
