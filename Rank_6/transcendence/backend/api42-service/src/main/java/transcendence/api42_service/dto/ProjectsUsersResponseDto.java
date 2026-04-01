package transcendence.api42_service.dto;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.time.OffsetDateTime;

public record ProjectsUsersResponseDto(
		Long id,
		Integer occurrence,
		Integer final_mark,
		String status,
		@JsonProperty("validated?")
		Boolean validated,
		OffsetDateTime marked_at,
		ProjectResponseDto project
) {
}