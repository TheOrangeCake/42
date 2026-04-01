package com.transcendence.auth.web;

import io.jsonwebtoken.Claims;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import com.transcendence.auth.security.JwtService;

import java.util.HashMap;
import java.util.Map;

@RestController
public class MeController {

  private final JwtService jwtService;

  @Value("${app.jwt.cookie-name:access_token}")
  private String cookieName;

  public MeController(JwtService jwtService) {
    this.jwtService = jwtService;
  }

  @GetMapping("/me")
  public ResponseEntity<?> me(HttpServletRequest request) {
    String token = readCookie(request, cookieName);

    if (token == null || token.isBlank()) {
      return ResponseEntity.ok(Map.of("authenticated", false));
    }

    try {
      Claims claims = jwtService.parse(token);

      Map<String, Object> body = new HashMap<>();
      body.put("authenticated", true);
      body.put("sub", claims.getSubject());
      body.put("email", claims.get("email"));
      body.put("iat", claims.getIssuedAt());
      body.put("exp", claims.getExpiration());
	  body.put("token", token);
      // si tu ajoutes plus de claims plus tard, tu les mets ici
      return ResponseEntity.ok(body);

    } catch (Exception e) {
      // token invalide/expiré
      return ResponseEntity.ok(Map.of("authenticated", false));
    }
  }

  private static String readCookie(HttpServletRequest request, String name) {
    Cookie[] cookies = request.getCookies();
    if (cookies == null) return null;
    for (Cookie c : cookies) {
      if (name.equals(c.getName())) return c.getValue();
    }
    return null;
  }
}
