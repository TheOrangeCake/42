package transcendence.api42_service.dto;

public record UserSimpleResponseDto(
		Long id,
		String login,
		String first_name,
		String last_name,
		String intra_url,
		String custom_avatar_url,
		AvatarDto image,
		String pool_month,
		String pool_year,
		Integer rank,
		Integer rank_progress_percent,
		Integer performance_score,
		String lfg
) {
}