package com.transcendence.group.security;

import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

@Component
public class AuthServiceClient {

    private final RestTemplate rest = new RestTemplate();

    public ResponseEntity<String> callMe(String cookieHeader) {
        HttpHeaders headers = new HttpHeaders();
        if (cookieHeader != null) {
            headers.set("Cookie", cookieHeader);
        }
        HttpEntity<Void> req = new HttpEntity<>(headers);

        // auth-service is the docker DNS name from inside the network
        return rest.exchange(
                "http://auth-service:8081/api/auth/me",
                HttpMethod.GET,
                req,
                String.class
        );
    }
}
