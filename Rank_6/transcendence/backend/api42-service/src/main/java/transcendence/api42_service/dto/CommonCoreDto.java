package transcendence.api42_service.dto;

import java.util.List;
import java.util.SortedMap;

public record CommonCoreDto(
		List<ProjectResponseDto> projects,
		SortedMap<Integer, CommonCoreRankDto> ranks
) {
}