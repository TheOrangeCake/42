package com.transcendance.chatservice.security;

import com.transcendance.chatservice.exception.InvalidJwtException;
import com.transcendance.chatservice.service.JwtService;
import io.jsonwebtoken.JwtException;
import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;
import org.springframework.web.filter.OncePerRequestFilter;

import java.io.IOException;
import java.util.Collections;

/**
 * JWT Authentication Filter for HTTP REST endpoints.
 * Extracts Bearer token from Authorization header and validates it.
 * Note: WebSocket authentication is handled separately in AuthChannelInterceptor.
 */
@Component
@RequiredArgsConstructor
public class JwtAuthenticationFilter extends OncePerRequestFilter {

    private final JwtService jwtService;

    @Override
    protected boolean shouldNotFilter(HttpServletRequest request) {
        String path = request.getServletPath();
        return path.startsWith("/actuator");
    }

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain)
            throws ServletException, IOException {
        try {
            String token = extractTokenFromRequest(request);

            if (token != null && StringUtils.hasText(token)) {
                try {
                    // Validate token and extract username
                    String username = jwtService.extractUsername(token);
                    
                    if (StringUtils.hasText(username)) {
                        // Create authentication token
                        UsernamePasswordAuthenticationToken authToken =
                                new UsernamePasswordAuthenticationToken(username, null, Collections.emptyList());
                        SecurityContextHolder.getContext().setAuthentication(authToken);
                    }
                } catch (JwtException e) {
                    throw new InvalidJwtException("Invalid or expired JWT token", e);
                }
            }

            filterChain.doFilter(request, response);

        } catch (InvalidJwtException e) {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.setContentType("application/json");
            response.getWriter().write("{\"error\": \"" + e.getMessage() + "\"}");
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.setContentType("application/json");
            response.getWriter().write("{\"error\": \"Authentication failed: " + e.getMessage() + "\"}");
        }
    }

    /**
     * Extract JWT token from Authorization header (Bearer scheme)
     */
    private String extractTokenFromRequest(HttpServletRequest request) {
        String authHeader = request.getHeader("Authorization");
        
        if (StringUtils.hasText(authHeader) && authHeader.startsWith("Bearer ")) {
            return authHeader.substring(7); // Remove "Bearer " prefix
        }
        
        return null;
    }
}
