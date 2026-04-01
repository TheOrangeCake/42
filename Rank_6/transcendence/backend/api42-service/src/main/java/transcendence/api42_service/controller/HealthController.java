package transcendence.api42_service.controller;

import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import transcendence.api42_service.bootstrap.StartupRunner;
import transcendence.api42_service.data_import.oauth.OauthTokenGetter;
import transcendence.api42_service.exception.ApiCallFailException;
import transcendence.api42_service.repositories.CampusRepository;
import transcendence.api42_service.repositories.ProjectRepository;
import transcendence.api42_service.repositories.ProjectsUsersRepository;
import transcendence.api42_service.repositories.UserRepository;
import transcendence.api42_service.scheduler.Updater;

import java.util.logging.Logger;

@RestController
@RequestMapping("/v1/api42/health")
@AllArgsConstructor
public class HealthController {
	private final OauthTokenGetter oauthTokenGetter;
	private final CampusRepository campusRepository;
	private final UserRepository userRepository;
	private final ProjectsUsersRepository projectsUsersRepository;
	private final ProjectRepository projectRepository;
	private final StartupRunner startupRunner;
	private final Updater updater;
	private final Logger logger;

	@GetMapping
	public ResponseEntity<String> healthCheck() {
		try {
			oauthTokenGetter.retrieveToken();
		} catch (ApiCallFailException e) {
			logger.severe("API error during Oauth Token request: " + e.getMessage());
			if (e.getStatus().value() == 401) {
				logger.severe("Api 42 Secret expired. Please update.");
				return ResponseEntity.status(500).body("Unhealthy: Api 42 Secret expired");
			}
			return ResponseEntity.status(500).body("Unhealthy: Unexpected error during OAuth Token request");
		} catch (Exception e) {
			logger.severe("Unexpected error during OAuth Token request: " + e.getMessage());
			return ResponseEntity.status(500).body("Unhealthy: Unexpected error during OAuth Token request");
		}

		if (!startupRunner.isStartupComplete()) {
				logger.warning("A request was made during database initialization");
				return ResponseEntity.status(500).body("Unhealthy: Initializing database");
			}
			if (!(campusRepository.count() > 0
				&& userRepository.count() > 0
				&& projectsUsersRepository.count() > 0
				&& projectRepository.count() > 0)) {
				logger.severe("Some databases are empty");
				return ResponseEntity.status(500).body("Unhealthy: Some databases are empty");
			}
			if (!updater.isFinishedUpdate()) {
				logger.warning("A request was made during database update");
				return ResponseEntity.ok("Healthy: Database is updating");
			}
			return ResponseEntity.ok("Healthy");

	}
}