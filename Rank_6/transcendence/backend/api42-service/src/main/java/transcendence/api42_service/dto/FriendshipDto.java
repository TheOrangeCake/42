package transcendence.api42_service.dto;

public record FriendshipDto(
	Long id,
	Long friend_id,
	String friend_login,
	String friend_avatar_url,
	String status,
	boolean is_requester,
	boolean online
) {
}
