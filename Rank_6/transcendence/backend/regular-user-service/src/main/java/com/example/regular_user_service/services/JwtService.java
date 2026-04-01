package com.example.regular_user_service.services;

import com.example.regular_user_service.entities.RevokedToken;
import com.example.regular_user_service.exception.BadTokenException;
import com.example.regular_user_service.repositories.RevokeTokenRepository;
import io.jsonwebtoken.ExpiredJwtException;
import io.jsonwebtoken.JwtException;
import io.jsonwebtoken.Jwts;

import java.util.Date;
import java.util.HexFormat;

import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletRequest;
import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

@Getter
@Service
public class JwtService {
	private final SecretKey secretKey;
	private final RevokeTokenRepository revokeTokenRepository;

	public JwtService(@Value("${REGULAR_USER_JWT_KEY}") String hexKey, RevokeTokenRepository revokeTokenRepository) {
        this.revokeTokenRepository = revokeTokenRepository;
        byte[] keyBytes = HexFormat.of().parseHex(hexKey);
		this.secretKey = new SecretKeySpec(keyBytes, "HmacSHA256");
	}

	public String generateAccessToken(Long id) {
		return Jwts.builder()
				.issuer("Regular User Service")
				.subject(id.toString())
				.issuedAt(new Date())
				.expiration(new Date(System.currentTimeMillis() + 15 * 60 * 1000))
				.signWith(secretKey)
				.compact();
	}

	public String generateRefreshToken(Long id) {
		return Jwts.builder()
				.issuer("Regular User Service")
				.subject(id.toString())
				.issuedAt(new Date())
				.expiration(new Date(System.currentTimeMillis() + 7L * 24 * 60 * 60 * 1000))
				.signWith(secretKey)
				.compact();
	}

	public void validateJwtToken(String jwtToken, String type) {
		if (jwtToken == null || jwtToken.isEmpty()) {
			throw new BadTokenException("Invalid access token: JWT token is null or empty");
		}
		try {
			Object issuer = Jwts.parser()
					.verifyWith(secretKey)
					.build()
					.parseSignedClaims(jwtToken)
					.getPayload()
					.getIssuer();
			if (issuer == null || !issuer.equals("Regular User Service"))
				throw new BadTokenException("Invalid " + type + ": wrong issuer");
			if(revokeTokenRepository.findById(jwtToken).isPresent())
				throw new BadTokenException("Invalid " + type + ": revoked token");
		} catch (ExpiredJwtException e) {
			if (type.equals("access token"))
				throw new BadTokenException("Invalid " + type + ": expired, please renew at /v1/user-regular/auth/refresh-token");
			else
				throw new BadTokenException("Invalid " + type + ": expired, please sign in again");
		} catch (JwtException e) {
			throw new BadTokenException("Invalid "  + type +  ": bad format or signature");
		}
	}

	public String getUserId(String jwtToken, String type) {
		if (jwtToken == null || jwtToken.isEmpty()) {
			throw new BadTokenException("Invalid access token: JWT token is null or empty");
		}
		String userId = Jwts.parser()
					.verifyWith(secretKey)
					.build()
					.parseSignedClaims(jwtToken)
					.getPayload()
					.getSubject();
		if (userId == null || userId.isEmpty()) {
			throw new BadTokenException("Invalid "  + type +  ": user ID not found");
		}
		return userId;
	}

	public String extractAccessToken(HttpServletRequest request) {
		String authHeader = request.getHeader("Authorization");
		if (authHeader != null && authHeader.startsWith("Bearer ")) {
            return authHeader.substring(7);
		} else {
			throw new BadTokenException("Invalid Authorization header");
		}
	}

	public String extractRefreshToken(HttpServletRequest request) {
		Cookie[] cookies = request.getCookies();
		if (cookies != null) {
			for (Cookie cookie : cookies) {
				if (cookie.getName().equals("refreshToken")) {
					String token = cookie.getValue();
					if (token == null || token.isEmpty()) {
						throw new BadTokenException("Refresh token cookie is empty");
					}
					return token;
				}
			}
		}
		throw new BadTokenException("Invalid Refresh Cookie");
	}

	public void revokeToken(String token, String type) {
		RevokedToken revokedToken = new RevokedToken();
		revokedToken.setToken(token);
		revokedToken.setType(type);
		revokedToken.setRevokedAt(new Date());
		revokeTokenRepository.save(revokedToken);
	}
}