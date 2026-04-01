package com.transcendence.group.web;

import java.util.LinkedHashMap;
import java.util.Map;

import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.security.oauth2.jwt.Jwt;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MeController {

  @GetMapping("/me")
  public Map<String, Object> me(@AuthenticationPrincipal Jwt jwt) {

    Map<String, Object> out = new LinkedHashMap<>();
    out.put("sub", jwt.getSubject());
    out.put("issuedAt", jwt.getIssuedAt());
    out.put("expiresAt", jwt.getExpiresAt());

    // Claims custom si tu les mets dans le token (login/email/campus_id/etc.)
    out.putAll(jwt.getClaims());
    return out;
  }
}
