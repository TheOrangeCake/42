package transcendence.api42_service.dto;

public record ProjectResponseDto(
		Long id,
		String name,
		String slug,
		int rank
) {
}