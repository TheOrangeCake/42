package com.transcendence.group.security;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.security.oauth2.server.resource.web.BearerTokenResolver;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;

import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletRequest;

@Component
public class CookieBearerTokenResolver implements BearerTokenResolver {

  private final String cookieName;

  public CookieBearerTokenResolver(
      @Value("${app.jwt.cookie-name:access_token}") String cookieName
  ) {
    this.cookieName = cookieName;
  }

  @Override
  public String resolve(HttpServletRequest request) {
    String auth = request.getHeader("Authorization");
    if (StringUtils.hasText(auth) && auth.startsWith("Bearer ")) {
      return auth.substring(7);
    }

    Cookie[] cookies = request.getCookies();
    if (cookies == null) return null;

    for (Cookie c : cookies) {
      if (cookieName.equals(c.getName()) && StringUtils.hasText(c.getValue())) {
        return c.getValue();
      }
    }
    return null;
  }
}
