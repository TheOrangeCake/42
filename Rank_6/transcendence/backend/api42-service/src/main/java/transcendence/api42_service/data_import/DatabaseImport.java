package transcendence.api42_service.data_import;

import lombok.RequiredArgsConstructor;
import me.tongfei.progressbar.ProgressBar;
import org.springframework.stereotype.Service;
import transcendence.api42_service.dto.PageResult;
import transcendence.api42_service.dto.mapper.CampusMapper;
import transcendence.api42_service.dto.mapper.UserMapper;
import transcendence.api42_service.entities.Campus;
import transcendence.api42_service.exception.ApiCallFailException;
import transcendence.api42_service.data_import.interfaces.EntitySaverInterface;
import transcendence.api42_service.data_import.interfaces.PageFetcherInterface;
import transcendence.api42_service.repositories.CampusRepository;
import transcendence.api42_service.repositories.UserRepository;

import java.util.Optional;
import java.util.logging.Logger;

@RequiredArgsConstructor
@Service
public class DatabaseImport {
	private final Api42Fetcher api42Fetcher;
	private final CampusMapper campusMapper;
	private final CampusRepository campusRepository;
	private final UserMapper userMapper;
	private final UserRepository userRepository;
	private final Logger logger;

	public void campusDbPopulate(String token) {
		String entityName = "CAMPUSES";
		populateDatabase(
				token,
				entityName,
				(t, p, rpp) -> api42Fetcher.fetchCampusDtoData(t, p, rpp)
						.mapItems(campusMapper::mapToCampus),
				campusRepository::saveAll
		);
	}

	public Campus getLausanneCampus() {
		Optional<Campus> lausanneCampusOptional = campusRepository.findByName("Lausanne");
		return lausanneCampusOptional.orElse(null);
	}

	public void userDbPopulate(String token) {
		String entityName = "USERS";

		// Hardcoded
		Campus lausanneCampus = getLausanneCampus();

		if (lausanneCampus != null) {
			Long lausanneCampusId = lausanneCampus.getId();
			populateDatabase(
					token,
					entityName,
					(t, p, rpp) -> api42Fetcher.fetchUserDtoData(t, p, rpp, lausanneCampusId)
							.mapItems(dto -> userMapper.mapRequestToUser(dto, lausanneCampus)),
					userRepository::saveAll
			);
		} else {
			logger.warning("There is no Lausanne campus in database, USERS database will be empty");
		}
	}

	@SuppressWarnings({"BusyWait", "ReassignedVariable"})
	public <T> void populateDatabase(
			String token,
			String entityName,
			PageFetcherInterface<T> fetcher,
			EntitySaverInterface<T> saver
	) {
		int page = 1;
		int resultPerPage = 100;

		try (ProgressBar pb = new ProgressBar("Fetching " + entityName, -1)) {
			while (true) {
				pb.step();
				try {
					PageResult<T> result = fetcher.fetch(token, page, resultPerPage);
					if (result.items().isEmpty()) break;
					saver.save(result.items());
					pb.maxHint((int) Math.ceil((double) result.xTotal() / resultPerPage));
					if (!result.hasNext()) {
						break;
					}
					page++;
					Thread.sleep(600);
				} catch (ApiCallFailException e) {
					if (e.getStatus().value() == 429) {
						handleRateLimit();
					} else if (e.getStatus().value() == 401) {
						logger.severe("Token expired, need a new token.");
						break;
					} else {
						logAndStop(entityName, e);
						break;
					}
				} catch (InterruptedException e) {
					Thread.currentThread().interrupt();
					logInterrupted(entityName);
					break;
				}
			}
		}
	}

	public void handleRateLimit() {
		try {
			logger.warning("Rate limit reached, retrying after 600ms");
			Thread.sleep(6000);
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
			logger.severe("Sleep interrupted, stopping initialization.");
		}
	}

	public void logAndStop(String entityName, ApiCallFailException e) {
		logger.severe("API error while initializing " + entityName + ": " + e.getMessage() + ". Initialization stopped.");
	}

	public void logInterrupted(String entityName) {
		logger.severe("Initialization of " + entityName + " interrupted. Stopping.");
	}
}
