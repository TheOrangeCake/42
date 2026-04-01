package transcendence.api42_service.definition.project;

import com.fasterxml.jackson.annotation.JsonProperty;

public record IndividualProject(
		@JsonProperty("cursus_project_id")
		Long cursusProjectId,
		String name,
		String slug,
		@JsonProperty("projects_users")
		LastProjectsUsers lastProjectsUsers
) {
}