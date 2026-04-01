package transcendence.api42_service.definition.project;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.List;

public record UserCommonCore (
		@JsonProperty("rank")
		List<IndividualRank> individualRanks
) {
}