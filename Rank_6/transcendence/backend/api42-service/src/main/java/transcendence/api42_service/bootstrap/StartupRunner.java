package transcendence.api42_service.bootstrap;

import lombok.Getter;
import lombok.RequiredArgsConstructor;
import org.jspecify.annotations.NonNull;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;
import transcendence.api42_service.data_import.ProjectsUsersImport;
import transcendence.api42_service.exception.ApiCallFailException;
import transcendence.api42_service.exception.InvalidTokenException;
import transcendence.api42_service.repositories.CampusRepository;
import transcendence.api42_service.repositories.ProjectsUsersRepository;
import transcendence.api42_service.repositories.UserRepository;
import transcendence.api42_service.data_import.DatabaseImport;
import transcendence.api42_service.data_import.oauth.OauthTokenGetter;
import transcendence.api42_service.services.UserProgressScoreCalculator;
import transcendence.api42_service.services.UserRankCalculator;
import transcendence.api42_service.services.UserTalentPointCalculator;

import java.util.logging.Logger;

@RequiredArgsConstructor
@Component
public class StartupRunner implements CommandLineRunner {
    private final OauthTokenGetter oauthTokenGetter;
    private final UserRepository userRepository;
    private final CampusRepository campusRepository;
    private final ProjectsUsersRepository projectsUsersRepository;
    private final DatabaseImport databaseImport;
    private final ProjectsUsersImport projectsUsersImport;
    private final UserRankCalculator userRankCalculator;
    private final UserProgressScoreCalculator userProgressScoreCalculator;
    private final UserTalentPointCalculator userTalentPointCalculator;
    private final Logger logger;

    @Getter
    private boolean startupComplete = false;

    @Override
    public void run(String @NonNull ... args) {
        System.out.println("""
                                                                   \s
                 _____     _ ___ ___    _____             _        \s
                |  _  |___|_| | |_  |  |   __|___ ___ _ _|_|___ ___\s
                |     | . | |_  |  _|  |__   | -_|  _| | | |  _| -_|
                |__|__|  _|_| |_|___|  |_____|___|_|  \\_/|_|___|___|
                      |_|                                          \s
                """);
        logger.info("Service is used to manage users data from 42. By Nguyen NGUYEN (hoannguy).");
        try {
            logger.info("Getting Oauth token.");
            oauthTokenGetter.retrieveToken();
        } catch (ApiCallFailException e) {
            logger.severe("API error during Oauth Token request: " + e.getMessage());
            return;
        } catch (InvalidTokenException e) {
            logger.severe("Invalid Oauth token for api call, check uid, secret or token refresh");
            return;
        }
        String token = oauthTokenGetter.getToken();
        logger.info("Fetching only Lausanne campus due to API rate limit");
        boolean needRecalculate = false;
        if (campusRepository.count() > 0) {
            logger.info("Campus database already initialized. Skip API fetch for Campus.");
        } else {
            databaseImport.campusDbPopulate(token);
            needRecalculate = true;
        }
        if (userRepository.count() > 0) {
            logger.info("User database already initialized. Skip API fetch for User.");
        } else {
            databaseImport.userDbPopulate(token);
            needRecalculate = true;
        }
        if (projectsUsersRepository.count() > 0) {
            logger.info("ProjectsUsers database already initialized. Skip API fetch for ProjectsUsers.");
        } else {
            projectsUsersImport.projectsUsersDbPopulate(token);
        }
        if (userRepository.count() > 0 && projectsUsersRepository.count() > 0 && needRecalculate)  {
            userRankCalculator.calculateUserRank();
            userProgressScoreCalculator.calculateUserScore();
            userTalentPointCalculator.calculateUserTalentPoint();
        } else if (userRepository.count() <= 0 && projectsUsersRepository.count() <= 0) {
            logger.severe("Databases user and projects users initialization failed");
            return;
        } else if (!needRecalculate) {
            logger.info("Data already calculated. Skip data calculation.");
        }
        this.startupComplete = true;
        logger.info("Database initialization completed.");
    }
}