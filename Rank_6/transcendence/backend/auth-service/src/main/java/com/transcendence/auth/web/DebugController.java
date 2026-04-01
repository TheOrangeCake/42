package com.transcendence.auth.web;

import org.springframework.http.MediaType;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.security.oauth2.core.user.OAuth2User;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@RestController
public class DebugController {

    // IMPORTANT: ce endpoint est PROTÉGÉ -> il marche seulement après login OAuth2 réussi
    @GetMapping(value = "/debug/oauth2-user", produces = MediaType.APPLICATION_JSON_VALUE)
    public Map<String, Object> oauth2User(@AuthenticationPrincipal OAuth2User user) {
        // retourne toutes les attributes issues de /v2/me (42)
        return user.getAttributes();
    }
}
