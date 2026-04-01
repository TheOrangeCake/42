package transcendence.api42_service.services;

import io.jsonwebtoken.ExpiredJwtException;
import io.jsonwebtoken.JwtException;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.security.Keys;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletRequest;
import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import transcendence.api42_service.exception.BadTokenException;

import javax.crypto.SecretKey;
import java.nio.charset.StandardCharsets;

@Getter
@Service
public class JwtService {
	private final SecretKey secretKey;

	public JwtService(@Value("${JWT_SECRET}") String key) {
		this.secretKey = Keys.hmacShaKeyFor(key.getBytes(StandardCharsets.UTF_8));
	}

	public void validateJwtToken(String jwtToken) {
		if (jwtToken == null || jwtToken.isEmpty()) {
			throw new BadTokenException("Invalid access token: JWT token is null or empty");
		}
		try {
			Object provider = Jwts.parser()
					.verifyWith(secretKey)
					.build()
					.parseSignedClaims(jwtToken)
					.getPayload()
					.get("provider");
			if (provider == null || !provider.equals("42"))
				throw new BadTokenException("Invalid access token: wrong provider");
		} catch (ExpiredJwtException e) {
				throw new BadTokenException("Invalid access token: expired");
		} catch (JwtException e) {
			throw new BadTokenException("Invalid access token: bad format or signature");
		}
	}

	public String getUserId(String jwtToken) {
		if (jwtToken == null || jwtToken.isEmpty()) {
			throw new BadTokenException("Invalid access token: JWT token is null or empty");
		}
		Object userId = Jwts.parser()
					.verifyWith(secretKey)
					.build()
					.parseSignedClaims(jwtToken)
					.getPayload()
					.get("uid");
		if (userId == null) {
			throw new BadTokenException("Invalid access token: user ID not found");
		}
		return userId.toString();
	}

	public String extractAccessToken(HttpServletRequest request) {
		Cookie[] cookies = request.getCookies();
		if (cookies != null) {
			for (Cookie cookie : cookies) {
				if (cookie.getName().equals("access_token")) {
					String token = cookie.getValue();
					if (token == null || token.isEmpty()) {
						throw new BadTokenException("Access token cookie is empty");
					}
					return token;
				}
			}
		}
		throw new BadTokenException("Invalid Access Token Cookie");
	}

}