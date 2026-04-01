package transcendence.api42_service.services;

import lombok.AllArgsConstructor;
import me.tongfei.progressbar.ProgressBar;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import transcendence.api42_service.definition.curriculum.CommonCoreCurriculum;
import transcendence.api42_service.definition.curriculum.RankDefinition;
import transcendence.api42_service.entities.User;
import transcendence.api42_service.repositories.UserRepository;

import java.util.Collections;
import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.logging.Logger;

@AllArgsConstructor
@Transactional
@Service
public class UserProgressScoreCalculator {
	private final UserRepository userRepository;
	private final Logger logger;

	@SuppressWarnings("ReassignedVariable")
	public void calculateUserScore() {
		logger.info("Calculate user current rank progress");
		List<User> activeUsers = Optional.ofNullable(userRepository.findByActiveTrue())
				.orElse(Collections.emptyList());

		if (activeUsers.isEmpty()) {
			logger.warning("No active users found.");
			return;
		}

		try (ProgressBar pb = new ProgressBar("Calculating user current rank progress", activeUsers.size())) {
			for (User user : activeUsers) {
				pb.step();
				int rankProgress = 0;
				Set<String> finishedProjects = Optional.ofNullable(user.getFinishedProjects())
						.orElse(Collections.emptySet());
				RankDefinition current = CommonCoreCurriculum.getRank(user.getRank());
				if (current != null) {
					int currentRankProjectsCount = current.mandatory().size() + current.choices().size();
					if (currentRankProjectsCount == 0) {
						user.setRankProgressPercent(rankProgress);
						break;
					}
					int currentRankFinishedCount = 0;
					for (String projectSlug : finishedProjects) {
						if (current.mandatory().contains(projectSlug)) {
							currentRankFinishedCount++;
							continue;
						}
						for (Set<String> choiceGroup : current.choices()) {
							if (choiceGroup != null && choiceGroup.contains(projectSlug)) {
								currentRankFinishedCount++;
								break;
							}
						}
					}
					rankProgress = (int) Math.ceil((double)currentRankFinishedCount / currentRankProjectsCount * 100);
				}
				user.setRankProgressPercent(rankProgress);
			}
		} catch (Exception e) {
			logger.severe("Failed to initialize progress bar: " + e.getMessage());
		}
		try {
			userRepository.saveAll(activeUsers);
		} catch (Exception e) {
			logger.severe("Failed to save user rank progress: " + e.getMessage());
		}
	}
}