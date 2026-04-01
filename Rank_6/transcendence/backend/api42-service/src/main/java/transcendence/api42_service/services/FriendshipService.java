package transcendence.api42_service.services;

import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;
import transcendence.api42_service.dto.EnvVariables;
import transcendence.api42_service.dto.FriendshipDto;
import transcendence.api42_service.entities.Friendship;
import transcendence.api42_service.entities.FriendshipStatus;
import transcendence.api42_service.entities.User;
import transcendence.api42_service.repositories.FriendshipRepository;
import transcendence.api42_service.repositories.UserRepository;

import java.util.List;

@Service
@RequiredArgsConstructor
public class FriendshipService {

	private final FriendshipRepository friendshipRepository;
	private final UserRepository userRepository;
	private final EnvVariables envVariables;

	public FriendshipDto sendRequest(Long requesterId, Long addresseeId) {
		if (requesterId.equals(addresseeId)) {
			throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Cannot send a friend request to yourself");
		}
		User requester = userRepository.findById(requesterId)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "User not found"));
		User addressee = userRepository.findById(addresseeId)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "Target user not found"));

		friendshipRepository.findBetweenUsers(requesterId, addresseeId).ifPresent(existing -> {
			if (existing.getStatus() == FriendshipStatus.ACCEPTED) {
				throw new ResponseStatusException(HttpStatus.CONFLICT, "Already friends");
			}
			if (existing.getStatus() == FriendshipStatus.PENDING) {
				throw new ResponseStatusException(HttpStatus.CONFLICT, "Friend request already pending");
			}
			if (existing.getStatus() == FriendshipStatus.DECLINED) {
				friendshipRepository.delete(existing);
			}
		});

		Friendship friendship = new Friendship();
		friendship.setRequester(requester);
		friendship.setAddressee(addressee);
		friendship.setStatus(FriendshipStatus.PENDING);
		friendshipRepository.save(friendship);
		return toDto(friendship, requesterId);
	}

	public FriendshipDto acceptRequest(Long userId, Long friendshipId) {
		Friendship friendship = getFriendshipOrThrow(friendshipId);
		if (!friendship.getAddressee().getId().equals(userId)) {
			throw new ResponseStatusException(HttpStatus.FORBIDDEN, "Only the addressee can accept a request");
		}
		if (friendship.getStatus() != FriendshipStatus.PENDING) {
			throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Request is not pending");
		}
		friendship.setStatus(FriendshipStatus.ACCEPTED);
		friendshipRepository.save(friendship);
		return toDto(friendship, userId);
	}

	public FriendshipDto declineRequest(Long userId, Long friendshipId) {
		Friendship friendship = getFriendshipOrThrow(friendshipId);
		if (!friendship.getAddressee().getId().equals(userId)) {
			throw new ResponseStatusException(HttpStatus.FORBIDDEN, "Only the addressee can decline a request");
		}
		if (friendship.getStatus() != FriendshipStatus.PENDING) {
			throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Request is not pending");
		}
		friendship.setStatus(FriendshipStatus.DECLINED);
		friendshipRepository.save(friendship);
		return toDto(friendship, userId);
	}

	public void removeFriend(Long userId, Long friendshipId) {
		Friendship friendship = getFriendshipOrThrow(friendshipId);
		if (!friendship.getRequester().getId().equals(userId) && !friendship.getAddressee().getId().equals(userId)) {
			throw new ResponseStatusException(HttpStatus.FORBIDDEN, "Not part of this friendship");
		}
		friendshipRepository.delete(friendship);
	}

	public List<FriendshipDto> getFriends(Long userId) {
		return friendshipRepository.findAcceptedFriendships(userId).stream()
				.map(f -> toDto(f, userId)).toList();
	}

	public List<FriendshipDto> getPendingRequests(Long userId) {
		return friendshipRepository.findPendingRequests(userId).stream()
				.map(f -> toDto(f, userId)).toList();
	}

	public List<FriendshipDto> getSentRequests(Long userId) {
		return friendshipRepository.findSentRequests(userId).stream()
				.map(f -> toDto(f, userId)).toList();
	}

	public boolean areFriends(Long userId1, Long userId2) {
		return friendshipRepository.findBetweenUsers(userId1, userId2)
				.map(f -> f.getStatus() == FriendshipStatus.ACCEPTED)
				.orElse(false);
	}

	private Friendship getFriendshipOrThrow(Long friendshipId) {
		return friendshipRepository.findById(friendshipId)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "Friendship not found"));
	}

	public void updateLastSeen(Long userId) {
		userRepository.findById(userId).ifPresent(user -> {
			user.setLastSeen(java.time.OffsetDateTime.now());
			userRepository.save(user);
		});
	}

	private boolean isOnline(User user) {
		if (user.getLastSeen() == null) return false;
		return user.getLastSeen().isAfter(java.time.OffsetDateTime.now().minusSeconds(60));
	}

	private FriendshipDto toDto(Friendship f, Long currentUserId) {
		boolean isRequester = f.getRequester().getId().equals(currentUserId);
		User friend = isRequester ? f.getAddressee() : f.getRequester();
		String avatarUrl = friend.getCustomAvatarUrl() != null
				? envVariables.getImageDomain() + friend.getCustomAvatarUrl()
				: friend.getImageMedium();
		return new FriendshipDto(
				f.getId(),
				friend.getId(),
				friend.getLogin(),
				avatarUrl,
				f.getStatus().name(),
				isRequester,
				isOnline(friend)
		);
	}
}
