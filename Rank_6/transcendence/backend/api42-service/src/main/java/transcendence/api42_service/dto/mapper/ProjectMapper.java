package transcendence.api42_service.dto.mapper;

import org.springframework.stereotype.Component;
import transcendence.api42_service.dto.ProjectResponseDto;
import transcendence.api42_service.entities.Project;

@Component
public final class ProjectMapper {
	public ProjectResponseDto mapToResponseDto(Project project) {
		return new ProjectResponseDto(
				project.getId(),
				project.getName(),
				project.getSlug(),
				project.getRank()
		);
	}
}