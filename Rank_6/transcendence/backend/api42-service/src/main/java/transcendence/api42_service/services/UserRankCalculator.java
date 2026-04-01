package transcendence.api42_service.services;

import lombok.AllArgsConstructor;
import me.tongfei.progressbar.ProgressBar;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import tools.jackson.databind.ObjectMapper;
import transcendence.api42_service.definition.curriculum.CommonCoreCurriculum;
import transcendence.api42_service.definition.curriculum.RankDefinition;
import transcendence.api42_service.definition.project.IndividualProject;
import transcendence.api42_service.definition.project.IndividualRank;
import transcendence.api42_service.definition.project.LastProjectsUsers;
import transcendence.api42_service.definition.project.UserCommonCore;
import transcendence.api42_service.entities.ProjectsUsers;
import transcendence.api42_service.entities.User;
import transcendence.api42_service.repositories.ProjectsUsersRepository;
import transcendence.api42_service.repositories.UserRepository;

import java.util.*;
import java.util.logging.Logger;

@AllArgsConstructor
@Transactional
@Service
public class UserRankCalculator {
	private final UserRepository userRepository;
	private final ProjectsUsersRepository projectsUsersRepository;
	private final ObjectMapper objectMapper;
	private final Logger logger;

	public void calculateUserRank() {
		logger.info("Calculate user current rank");
		List<User> activeUsers = Optional.ofNullable(userRepository.findByActiveTrue())
				.orElse(Collections.emptyList());
		List<ProjectsUsers> activeUsersProjectsUsers = Optional.ofNullable(projectsUsersRepository.findByUserIn(activeUsers))
				.orElse(Collections.emptyList());
		if (activeUsers.isEmpty()) {
			logger.warning("No active users found.");
			return;
		}

		try (ProgressBar pb = new ProgressBar("Calculating user current rank", activeUsers.size())) {
			for (User user : activeUsers) {
				pb.step();
				Map<String, ProjectsUsers> lastedProjectsUsersBySlug = UserTalentPointCalculator.getLastedProjectsUsersBySlug(user, activeUsersProjectsUsers);
				UserCommonCore userCommonCore = calculateUserCommonCore(user, lastedProjectsUsersBySlug);
				try {
					user.setDetailedProfileJson(toJson(userCommonCore));
				} catch (RuntimeException e) {
					logger.severe("Failed to serialize UserCommonCore and calculate rank for user " + user.getId().toString() + ": " + e);
					user.setDetailedProfileJson(null);
				}
			}
		} catch (Exception e) {
			logger.severe("Failed to initialize progress bar: " + e.getMessage());
			return;
		}
		try {
			userRepository.saveAll(activeUsers);
		} catch (Exception e) {
			logger.severe("Failed to save user ranks: " + e.getMessage());
		}
	}

	private IndividualProject setIndividualProject(ProjectsUsers projectsUsers) {
		if (projectsUsers == null || projectsUsers.getProject() == null) {
			throw new IllegalArgumentException("ProjectsUsers and its project cannot be null");
		}
		LastProjectsUsers lastProjectsUsers = new LastProjectsUsers(
				projectsUsers.getOccurrence(),
				projectsUsers.getFinalMark(),
				projectsUsers.getStatus(),
				projectsUsers.getValidated());
		return new IndividualProject(
				projectsUsers.getProject().getId(),
				projectsUsers.getProject().getName(),
				projectsUsers.getProject().getSlug(),
				lastProjectsUsers);
	}

	@SuppressWarnings("ReassignedVariable")
	public UserCommonCore calculateUserCommonCore(User user, Map<String, ProjectsUsers> lastedProjectsUsersBySlug) {
		if (user == null || lastedProjectsUsersBySlug == null) {
			throw new IllegalArgumentException("User and lastedProjectsUsersBySlug cannot be null");
		}
		Integer currentRank = 0;
		List<IndividualRank> ranks = new ArrayList<>();
		Set<String> finishedProjects = new HashSet<>();

		for (Map.Entry<Integer, RankDefinition> entry : CommonCoreCurriculum.RANKS.entrySet()) {
			if (entry.getValue() == null) {
				continue;
			}
			boolean rankCompleted = true;
			List<IndividualProject> projects = new ArrayList<>();
			for (String projectSlug : entry.getValue().mandatory()) {
				ProjectsUsers projectsUsers = lastedProjectsUsersBySlug.get(projectSlug);
				if (projectsUsers != null) {
					IndividualProject project = setIndividualProject(projectsUsers);
					projects.add(project);
					if (isProjectFinished(project)) {
						finishedProjects.add(projectSlug);
					} else {
						rankCompleted = false;
					}
				} else {
					rankCompleted = false;
				}
			}
			for (Set<String> choiceGroups : entry.getValue().choices()) {
				if (choiceGroups == null) {
					continue;
				}
				boolean choicesCompleted = false;
				for (String projectSlug : choiceGroups) {
					ProjectsUsers projectsUsers = lastedProjectsUsersBySlug.get(projectSlug);
					if (projectsUsers != null) {
						IndividualProject project = setIndividualProject(projectsUsers);
						projects.add(project);
						if (isProjectFinished(project)) {
							choicesCompleted = true;
							finishedProjects.add(projectSlug);
						}
					}
				}
				if (!choicesCompleted) {
					rankCompleted = false;
				}
			}
			IndividualRank rank = new IndividualRank(entry.getKey(), projects);
			ranks.add(rank);
			if (!rankCompleted) {
				break;
			} else {
				currentRank++;
			}
		}
		user.setRank(currentRank);
		user.setFreezeDays(currentRank * 6);
		user.setFinishedProjects(finishedProjects);
		user.setEligibleProjects(eligibleProjects(currentRank, finishedProjects));
		return new UserCommonCore(ranks);
	}

	private boolean isProjectFinished(IndividualProject project) {
		if (project == null || project.lastProjectsUsers() == null) {
			return false;
		}
		Boolean validated = project.lastProjectsUsers().validated();
		return validated != null && validated;
	}

	private Set<String> eligibleProjects(Integer userRank, Set<String> finishedProjects) {
		Set<String> eligibleProjects = new HashSet<>();
		RankDefinition current = CommonCoreCurriculum.getRank(userRank);
		RankDefinition next = CommonCoreCurriculum.getRank(userRank + 1);

		if (current != null) {
			for (String projectSlug : current.mandatory()) {
				if (!finishedProjects.contains(projectSlug)) {
					eligibleProjects.add(projectSlug);
				}
			}
			for (Set<String> choiceGroup : current.choices()) {
				if (choiceGroup != null) {
					boolean anyFinished = choiceGroup.stream().anyMatch(finishedProjects::contains);
					if (anyFinished) {
						eligibleProjects.addAll(choiceGroup);
					}
				}
			}
		}
		if (next != null) {
			eligibleProjects.addAll(next.mandatory());
			for (Set<String> choiceGroup : next.choices()) {
				if (choiceGroup != null) {
					eligibleProjects.addAll(choiceGroup);
				}
			}
		}
		return eligibleProjects;
	}

	private String toJson(UserCommonCore userCommonCore) {
		if (userCommonCore == null) {
			throw new IllegalArgumentException("UserCommonCore cannot be null");
		}

		try {
			return objectMapper.writeValueAsString(userCommonCore);
		} catch (Exception e) {
			logger.severe("Failed to serialize UserCommonCore: " + e.getMessage());
			throw new RuntimeException("Failed to serialize UserCommonCore", e);
		}
	}

}