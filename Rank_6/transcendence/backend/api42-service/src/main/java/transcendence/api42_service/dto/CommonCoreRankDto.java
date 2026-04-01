package transcendence.api42_service.dto;

import java.util.Set;

public record CommonCoreRankDto(
		Set<String> mandatory,
		Set<Set<String>> choices
) {
}