package transcendence.api42_service.definition.project;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.List;

public record IndividualRank(
		Integer rank,
		@JsonProperty("projects")
		List<IndividualProject> individualProject
) {
}