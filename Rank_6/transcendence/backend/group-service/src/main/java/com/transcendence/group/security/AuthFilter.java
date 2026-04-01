package com.transcendence.group.security;

import java.io.IOException;

import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

@Component
public class AuthFilter extends OncePerRequestFilter {

    private final AuthServiceClient auth;

    public AuthFilter(AuthServiceClient auth) {
        this.auth = auth;
    }

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain chain)
            throws ServletException, IOException {

        String path = request.getRequestURI();
        if (path.startsWith("/api/group/public/") || path.startsWith("/api/group/actuator/")) {
            chain.doFilter(request, response);
            return;
        }

        String cookie = request.getHeader("Cookie");
        ResponseEntity<String> me = auth.callMe(cookie);

        if (me.getStatusCodeValue() == 401) {
            response.setStatus(401);
            return;
        }

        request.setAttribute("auth.me", me.getBody());

        chain.doFilter(request, response);
    }
}
