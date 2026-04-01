package transcendence.api42_service.config;

import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import org.jspecify.annotations.NonNull;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;
import transcendence.api42_service.exception.BadTokenException;
import transcendence.api42_service.services.JwtService;

import java.io.IOException;
import java.util.Collections;

@RequiredArgsConstructor
@Component
public class JwtFilter extends OncePerRequestFilter {
	private final JwtService jwtService;

	@Override
	public void doFilterInternal(@NonNull HttpServletRequest request, @NonNull HttpServletResponse response, @NonNull FilterChain filterChain) throws IOException, ServletException {
		if (isPublicEndpoint(request)) {
			filterChain.doFilter(request, response);
			return;
		}
		try {
			String jwtToken = jwtService.extractAccessToken(request);
			jwtService.validateJwtToken(jwtToken);
			String userId = jwtService.getUserId(jwtToken);
			UsernamePasswordAuthenticationToken authToken = new UsernamePasswordAuthenticationToken(userId, null, Collections.emptyList());
			SecurityContextHolder.getContext().setAuthentication(authToken);
			filterChain.doFilter(request, response);
		} catch (BadTokenException e) {
			response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
			response.getWriter().write("{\"error\": \"" + e.getMessage() + "\"}");
			response.setContentType("application/json");
		}
	}

	private boolean isPublicEndpoint(HttpServletRequest request) {
		if (request == null) {
			return false;
		}
		String path = request.getRequestURI();
		return path.startsWith("/v1/api42/commoncore") ||
				path.startsWith("/error") ||
				path.startsWith("/images42/") ||
				path.startsWith("/actuator/") ||
				path.equals("/v1/api42/health") ||
				path.equals("/v1/api42/campuses") ||
				path.equals("/v1/42users/friends/check-internal") ||
				path.equals(("/h2-console"));
	}
}