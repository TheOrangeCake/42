package transcendence.api42_service.controller;

import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.*;
import transcendence.api42_service.dto.EnvVariables;
import transcendence.api42_service.dto.FriendshipDto;
import transcendence.api42_service.entities.User;
import transcendence.api42_service.exception.BadTokenException;
import transcendence.api42_service.repositories.UserRepository;
import transcendence.api42_service.services.FriendshipService;

import java.util.List;
import java.util.Map;

@AllArgsConstructor
@RestController
@RequestMapping("v1/42users/friends")
public class FriendshipController {
	private final EnvVariables envVariables;

	private final FriendshipService friendshipService;
	private final UserRepository userRepository;

	@PostMapping("/{userId}")
	public ResponseEntity<FriendshipDto> sendRequest(@PathVariable Long userId) {
		return ResponseEntity.ok(friendshipService.sendRequest(getUserId(), userId));
	}

	@PutMapping("/{friendshipId}/accept")
	public ResponseEntity<FriendshipDto> acceptRequest(@PathVariable Long friendshipId) {
		return ResponseEntity.ok(friendshipService.acceptRequest(getUserId(), friendshipId));
	}

	@PutMapping("/{friendshipId}/decline")
	public ResponseEntity<FriendshipDto> declineRequest(@PathVariable Long friendshipId) {
		return ResponseEntity.ok(friendshipService.declineRequest(getUserId(), friendshipId));
	}

	@DeleteMapping("/{friendshipId}")
	public ResponseEntity<Void> removeFriend(@PathVariable Long friendshipId) {
		friendshipService.removeFriend(getUserId(), friendshipId);
		return ResponseEntity.noContent().build();
	}

	@GetMapping
	public ResponseEntity<List<FriendshipDto>> getFriends() {
		return ResponseEntity.ok(friendshipService.getFriends(getUserId()));
	}

	@GetMapping("/pending")
	public ResponseEntity<List<FriendshipDto>> getPendingRequests() {
		return ResponseEntity.ok(friendshipService.getPendingRequests(getUserId()));
	}

	@GetMapping("/sent")
	public ResponseEntity<List<FriendshipDto>> getSentRequests() {
		return ResponseEntity.ok(friendshipService.getSentRequests(getUserId()));
	}

	private String getAvatar(User user) {
		if (user.getCustomAvatarUrl() == null) {
			return user.getImageMedium() != null ? user.getImageMedium() : envVariables.getImageDomain() + envVariables.getDefaultAvatar();
		}
		return envVariables.getImageDomain() + user.getCustomAvatarUrl();
	}

	@GetMapping("/search")
	public ResponseEntity<List<Map<String, Object>>> searchUsers(@RequestParam String login) {
		Long currentUserId = getUserId();
		List<Map<String, Object>> results = userRepository.findByLoginContainingIgnoreCase(login).stream()
				.filter(u -> !u.getId().equals(currentUserId))
				.limit(10)
				.map(u -> Map.<String, Object>of(
						"id", u.getId(),
						"login", u.getLogin(),
						"avatar_url", getAvatar(u)
				))
				.toList();
		return ResponseEntity.ok(results);
	}

	@GetMapping("/check/{userId}")
	public ResponseEntity<Map<String, Boolean>> checkFriendship(@PathVariable Long userId) {
		return ResponseEntity.ok(Map.of("friends", friendshipService.areFriends(getUserId(), userId)));
	}

	@PostMapping("/heartbeat")
	public ResponseEntity<Void> heartbeat() {
		friendshipService.updateLastSeen(getUserId());
		return ResponseEntity.ok().build();
	}

	@GetMapping("/check-internal")
	public ResponseEntity<Map<String, Boolean>> checkFriendshipInternal(
			@RequestParam String user1, @RequestParam String user2) {
		return userRepository.findByLogin(user1)
				.flatMap(u1 -> userRepository.findByLogin(user2)
						.map(u2 -> ResponseEntity.ok(Map.of("friends", friendshipService.areFriends(u1.getId(), u2.getId())))))
				.orElse(ResponseEntity.ok(Map.of("friends", false)));
	}

	private Long getUserId() {
		Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
		if (authentication == null || authentication.getPrincipal() == null) {
			throw new BadTokenException("Invalid access token: User Id not found");
		}
		return Long.parseLong(authentication.getPrincipal().toString());
	}
}
