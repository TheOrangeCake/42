package com.transcendance.chatservice.service;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.security.Keys;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import java.security.Key;
import java.util.HashMap;
import java.util.Date;
import java.util.function.Function;

@Service
public class JwtService {

    // CETTE CLÉ DOIT ÊTRE LA MÊME QUE DANS TON MICROSERVICE AUTH
    @Value("${app.jwt.secret}")
    private String secretKey;

    public String extractUsername(String token) {
        return extractClaim(token, Claims::getSubject);
    }

    public <T> T extractClaim(String token, Function<Claims, T> claimsResolver) {
        final Claims claims = extractAllClaims(token);
        return claimsResolver.apply(claims);
    }

    private Claims extractAllClaims(String token) {
        return Jwts.parserBuilder()
                .setSigningKey(getSignInKey())
                .build()
                .parseClaimsJws(token)
                .getBody();
    }

    private Key getSignInKey() {
        return Keys.hmacShaKeyFor(secretKey.getBytes());
    }

	public String generateTokenForTest(String username) {
    return Jwts.builder()
            .setClaims(new HashMap<>())
            .setSubject(username) 
            .setIssuedAt(new Date(System.currentTimeMillis()))
            .setExpiration(new Date(System.currentTimeMillis() + 1000 * 60 * 60 * 10)) // Valide 10 heures
            .signWith(getSignInKey(), io.jsonwebtoken.SignatureAlgorithm.HS256)
            .compact();
}
}

