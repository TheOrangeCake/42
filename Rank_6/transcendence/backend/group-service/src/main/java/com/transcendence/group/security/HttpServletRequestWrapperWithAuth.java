package com.transcendence.group.security;

import java.util.Collections;
import java.util.Enumeration;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletRequestWrapper;

public class HttpServletRequestWrapperWithAuth extends HttpServletRequestWrapper {

  private final String authHeader;

  public HttpServletRequestWrapperWithAuth(HttpServletRequest request, String authHeader) {
    super(request);
    this.authHeader = authHeader;
  }

  @Override
  public String getHeader(String name) {
    if ("Authorization".equalsIgnoreCase(name)) {
      return authHeader;
    }
    return super.getHeader(name);
  }

  @Override
  public Enumeration<String> getHeaders(String name) {
    if ("Authorization".equalsIgnoreCase(name)) {
      return Collections.enumeration(Collections.singletonList(authHeader));
    }
    return super.getHeaders(name);
  }
}
