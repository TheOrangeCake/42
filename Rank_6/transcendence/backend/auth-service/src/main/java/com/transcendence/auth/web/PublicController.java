package com.transcendence.auth.web;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class PublicController {

  @GetMapping("/public/ping")
  public String ping() {
    return "auth-service ok";
  }
}
