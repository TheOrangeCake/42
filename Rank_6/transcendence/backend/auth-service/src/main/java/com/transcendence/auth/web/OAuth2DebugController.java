package com.transcendence.auth.web;

import java.util.Map;

import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.security.oauth2.client.authentication.OAuth2AuthenticationToken;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class OAuth2DebugController {

  @GetMapping("/debug/oauth2-user")
  public Object me(@AuthenticationPrincipal Object principal,
                   OAuth2AuthenticationToken token) {

    if (token == null) {
      return Map.of("authenticated", false, "message", "No OAuth2AuthenticationToken (not logged in?)");
    }

    return Map.of(
      "authenticated", true,
      "registrationId", token.getAuthorizedClientRegistrationId(),
      "name", token.getName(),
      "authorities", token.getAuthorities(),
      "attributes", token.getPrincipal().getAttributes()
    );
  }
}
