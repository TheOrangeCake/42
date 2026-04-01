package com.example.regular_user_service.config;

import com.example.regular_user_service.entities.User;
import com.example.regular_user_service.exception.BadTokenException;
import com.example.regular_user_service.repositories.UserRepository;
import com.example.regular_user_service.services.JwtService;
import jakarta.servlet.*;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.jspecify.annotations.NonNull;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;

import java.io.IOException;
import java.util.Collections;

@RequiredArgsConstructor
@Component
public class JwtFilter extends OncePerRequestFilter {
	private final JwtService jwtService;
	private final UserRepository userRepository;

	@Override
	public void doFilterInternal(@NonNull HttpServletRequest request, @NonNull HttpServletResponse response, @NonNull FilterChain filterChain) throws IOException, ServletException {
		if (isPublicEndpoint(request)) {
			filterChain.doFilter(request, response);
			return;
		}
		try {
			String jwtToken = jwtService.extractAccessToken(request);
			jwtService.validateJwtToken(jwtToken, "access token");
			String userId = jwtService.getUserId(jwtToken, "access token");
			isAccountActive(userId);
			UsernamePasswordAuthenticationToken authToken = new UsernamePasswordAuthenticationToken(userId, null, Collections.emptyList());
			SecurityContextHolder.getContext().setAuthentication(authToken);
			filterChain.doFilter(request, response);
		} catch (RuntimeException e) {
			response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
			response.getWriter().write("{\"error\": \"" + e.getMessage() + "\"}");
			response.setContentType("application/json");
		}
	}

	private boolean isPublicEndpoint(HttpServletRequest request) {
		String path = request.getRequestURI();
		return path.startsWith("/v1/regular-user/auth/") ||
				path.startsWith("/actuator/") ||
				path.startsWith("/error") ||
				path.startsWith("/images-regular/") ||
				path.equals("/v1/regular-user/health") ||
				path.equals(("/h2-console"));
	}

	private void isAccountActive(String userId) {
		User user = userRepository.findUserById(Long.parseLong(userId)).orElseThrow(() -> new RuntimeException("Account is inactive or does not exist"));
		if (!user.isActive()) {
			throw new RuntimeException("Account is inactive or does not exist");
		}
	}
}