package transcendence.api42_service.dto.mapper;

import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;
import transcendence.api42_service.definition.curriculum.CommonCoreCurriculum;
import transcendence.api42_service.dto.ProjectsUsersRequestDto;
import transcendence.api42_service.dto.ProjectsUsersResponseDto;
import transcendence.api42_service.entities.Project;
import transcendence.api42_service.entities.ProjectsUsers;
import transcendence.api42_service.entities.User;
import transcendence.api42_service.repositories.ProjectRepository;
import transcendence.api42_service.repositories.ProjectsUsersRepository;

import java.util.Optional;

@AllArgsConstructor
@Component
public final class ProjectsUsersMapper {
	private final ProjectRepository projectRepository;
	private final ProjectsUsersRepository projectsUsersRepository;

	public ProjectsUsers mapToProjectsUsers(
			ProjectsUsersRequestDto projectsUsersDto,
			User user) {
		if (projectsUsersDto == null) {
			return null;
		}
		ProjectsUsers projectsUsers;
		Optional<ProjectsUsers> existingProjectsUsers = projectsUsersRepository.findById(projectsUsersDto.id());
		if (existingProjectsUsers.isPresent()) {
			projectsUsers = populateProjectsUsers(existingProjectsUsers.get(), projectsUsersDto);
		} else {
			projectsUsers = new ProjectsUsers();
			populateProjectsUsers(projectsUsers, projectsUsersDto);
			projectsUsers.setId(projectsUsersDto.id());
			projectsUsers.setUser(user);
			projectsUsers.setProject(mapToProject(projectsUsersDto));
		}
		return projectsUsers;
	}

	private ProjectsUsers populateProjectsUsers(ProjectsUsers projectsUsers, ProjectsUsersRequestDto projectsUsersDto) {
		projectsUsers.setOccurrence(projectsUsersDto.occurrence());
		projectsUsers.setFinalMark(projectsUsersDto.final_mark());
		projectsUsers.setStatus(projectsUsersDto.status());
		projectsUsers.setValidated(projectsUsersDto.validated());
		projectsUsers.setMarkedAt(projectsUsersDto.marked_at());
		return projectsUsers;
	}

	private Project mapToProject(ProjectsUsersRequestDto projectsUsersDto) {
		Optional<Project> projectOptional = projectRepository.findById(projectsUsersDto.project().id());
		Project project;
		if (projectOptional.isPresent()) {
			project = projectOptional.get();
		} else {
			project = new Project();
			project.setId(projectsUsersDto.project().id());
			project.setName(projectsUsersDto.project().name());
			project.setSlug(projectsUsersDto.project().slug());
			project.setRank(CommonCoreCurriculum.getProjectRank(projectsUsersDto.project().slug()));
			projectRepository.save(project);
		}
		return project;
	}
}