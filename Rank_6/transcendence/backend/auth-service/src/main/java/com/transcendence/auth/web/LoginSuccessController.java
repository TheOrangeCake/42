package com.transcendence.auth.web;

import java.util.Map;

import org.springframework.http.MediaType;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.security.oauth2.core.user.OAuth2User;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class LoginSuccessController {

    // A simple page the browser can show after OAuth login
    @GetMapping(value = "/login/success", produces = MediaType.TEXT_HTML_VALUE)
    public String successPage() {
        return """
            <html>
              <head><title>Auth OK</title></head>
              <body style="font-family: sans-serif">
                <h1>✅ OAuth login success</h1>
                <ul>
                  <li><a href="/api/auth/debug/oauth2-user">See OAuth2 user (JSON)</a></li>
                  <li><a href="/api/auth/whoami">Who am I (light JSON)</a></li>
                </ul>
              </body>
            </html>
        """;
    }

    @GetMapping("/whoami")
    public Map<String, Object> whoAmI(@AuthenticationPrincipal OAuth2User user) {
        if (user == null) {
            return Map.of("authenticated", false);
        }
        return Map.of(
            "authenticated", true,
            "name", user.getName(),
            "attributesKeys", user.getAttributes().keySet()
        );
    }
}
