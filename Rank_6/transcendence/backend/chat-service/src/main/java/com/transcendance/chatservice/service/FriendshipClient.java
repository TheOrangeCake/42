package com.transcendance.chatservice.service;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

import java.util.Map;

@Component
public class FriendshipClient {

	private final RestTemplate restTemplate = new RestTemplate();

	@Value("${app.api42-service.url:http://api42-service:8084}")
	private String api42ServiceUrl;

	public boolean areFriends(String userId1, String userId2) {
		try {
			String url = api42ServiceUrl + "/v1/42users/friends/check-internal?user1=" + userId1 + "&user2=" + userId2;
			@SuppressWarnings("unchecked")
			Map<String, Boolean> response = restTemplate.getForObject(url, Map.class);
			return response != null && Boolean.TRUE.equals(response.get("friends"));
		} catch (Exception e) {
			return false;
		}
	}
}
