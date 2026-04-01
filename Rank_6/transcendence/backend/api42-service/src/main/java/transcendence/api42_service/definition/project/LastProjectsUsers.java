package transcendence.api42_service.definition.project;

import com.fasterxml.jackson.annotation.JsonProperty;

public record LastProjectsUsers(
		Integer occurrence,
		@JsonProperty("final_mark")
		Integer finalMark,
		String status,
		Boolean validated
) {
}