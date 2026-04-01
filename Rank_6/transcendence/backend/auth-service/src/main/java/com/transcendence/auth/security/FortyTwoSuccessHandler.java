package com.transcendence.auth.security;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.http.HttpHeaders;
import org.springframework.http.ResponseCookie;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.security.core.Authentication;
import org.springframework.security.oauth2.client.authentication.OAuth2AuthenticationToken;
import org.springframework.security.web.authentication.AuthenticationSuccessHandler;
import org.springframework.stereotype.Component;

@Component
public class FortyTwoSuccessHandler implements AuthenticationSuccessHandler {

    private final JwtService jwtService;
    private final String cookieName;
    private final String frontendBaseUrl;

    public FortyTwoSuccessHandler(
            JwtService jwtService,
            @Value("${app.jwt.cookie-name:access_token}") String cookieName,
            @Value("${app.frontend.base-url:http://localhost:8080}") String frontendBaseUrl) {
        this.jwtService = jwtService;
        this.cookieName = cookieName;
        this.frontendBaseUrl = frontendBaseUrl;
    }

    @Override
    public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response,
                                        Authentication authentication) throws IOException, ServletException {

        OAuth2AuthenticationToken oauth = (OAuth2AuthenticationToken) authentication;
        Map<String, Object> attrs = oauth.getPrincipal().getAttributes();

        String login = safeString(attrs.get("login"));
        String id = String.valueOf(attrs.get("id"));

        if (login == null || login.isBlank()) {
            response.setStatus(403);
            response.setContentType("application/json");
            response.getWriter().write("{\"error\":\"access_denied\"}");
            return;
        }

        Map<String, Object> claims = new HashMap<>();
        claims.put("provider", "42");
        claims.put("uid", id);

        String jwt = jwtService.createToken(login, claims);

        ResponseCookie cookie = ResponseCookie.from(cookieName, jwt)
                .httpOnly(true)
                .path("/")
                .secure(true)
                .sameSite("Lax")
                .maxAge(60 * 60 * 2)
                .build();
        response.addHeader(HttpHeaders.SET_COOKIE, cookie.toString());

        String target = frontendBaseUrl.endsWith("/") ? frontendBaseUrl : (frontendBaseUrl + "/");
        response.setStatus(302);
        response.setHeader("Location", target);
    }

    private String safeString(Object v) {
        return v == null ? null : String.valueOf(v);
    }
}
