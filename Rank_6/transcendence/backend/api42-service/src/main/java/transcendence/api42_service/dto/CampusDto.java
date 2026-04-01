package transcendence.api42_service.dto;

import com.fasterxml.jackson.annotation.JsonProperty;

public record CampusDto(
		Long id,
		String name,
		String time_zone,
		Long users_count,
		String country,
		String address,
		String zip,
		String city,
		String website,
		String facebook,
		String twitter,
		Boolean active,

		@JsonProperty("public")
		Boolean publicCampus,

		String email_extension
) {}
