package com.transcendence.group.web;

import java.util.Map;

import org.springframework.security.core.Authentication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class SecureController {

  @GetMapping("/secure")
  public Map<String, Object> secure(Authentication auth) {
    return Map.of(
      "message", "you are authenticated",
      "principal", auth.getName(),
      "authorities", auth.getAuthorities().toString()
    );
  }
}
