package transcendence.api42_service.data_import;

import lombok.AllArgsConstructor;
import me.tongfei.progressbar.ProgressBar;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import transcendence.api42_service.data_import.interfaces.EntitySaverInterface;
import transcendence.api42_service.data_import.interfaces.PageFetcherInterface;
import transcendence.api42_service.dto.PageResult;
import transcendence.api42_service.dto.mapper.ProjectsUsersMapper;
import transcendence.api42_service.entities.Campus;
import transcendence.api42_service.entities.User;
import transcendence.api42_service.exception.ApiCallFailException;
import transcendence.api42_service.repositories.ProjectsUsersRepository;
import transcendence.api42_service.repositories.UserRepository;

import java.util.List;
import java.util.logging.Logger;

@AllArgsConstructor
@Service
public class ProjectsUsersImport {
	private final ProjectsUsersRepository projectsUsersRepository;
	private final UserRepository userRepository;
	private final Api42Fetcher api42Fetcher;
	private final ProjectsUsersMapper projectsUsersMapper;
	private final DatabaseImport databaseImport;
	private final Logger logger;


	@Transactional
	public void projectsUsersDbPopulate(String token) {
		String entityName = "PROJECTS_USERS";

		// Hardcoded
		Campus lausanneCampus = databaseImport.getLausanneCampus();

		if (userRepository.count() > 0 && lausanneCampus != null) {
			Long lausanneCampusId = lausanneCampus.getId();
			List<User> activeUsers = userRepository.findByActiveTrue();
			initialize(activeUsers, token, lausanneCampusId, entityName);
		} else {
			logger.warning("There is no user in the user database, PROJECTS_USERS database will be empty");
		}
	}
	@Transactional
	public void initialize(List<User> users, String token, Long lausanneCampusId, String entityName) {
		try (ProgressBar pb = new ProgressBar("Fetching " + entityName, users.size())) {
			for (User user : users) {
				pb.step();
				Long userId = user.getId();
				try {
					initializeUserProjects(user, token, lausanneCampusId, entityName);
				} catch (Exception e) {
					logger.severe("Failed to initialize projects for user " + userId + ": " + e.getMessage());
				}
			}
		}
	}

	@Transactional
	public void initializeUserProjects(User user, String token, Long campusId, String entityName) {
		// Hard coded
		int cursusId = 21;

		initializeDatabase(
				token,
				entityName,
				(t, p, rpp) -> api42Fetcher.fetchProjectsUsersDtoData(t, p, rpp, user.getId(), cursusId, campusId)
						.mapItems(dto -> projectsUsersMapper.mapToProjectsUsers(dto, user)),
				projectsUsersRepository::saveAll
		);
	}


	@SuppressWarnings({"BusyWait", "ReassignedVariable"})
	private <T> void initializeDatabase(
			String token,
			String entityName,
			PageFetcherInterface<T> fetcher,
			EntitySaverInterface<T> saver
	) {
		int page = 1;
		int resultPerPage = 100;

		while (true) {
			try {
				PageResult<T> result = fetcher.fetch(token, page, resultPerPage);
				if (result.items().isEmpty()) break;
				saver.save(result.items());
				if (!result.hasNext()) {
					break;
				}
				page++;
				Thread.sleep(600);
			} catch (ApiCallFailException e) {
				if (e.getStatus().value() == 429) {
					databaseImport.handleRateLimit();
				} else if (e.getStatus().value() == 401) {
					logger.severe("Token expired, need a new token.");
					break;
				} else {
					databaseImport.logAndStop(entityName, e);
					break;
				}
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
				databaseImport.logInterrupted(entityName);
				break;
			}
		}
	}
}