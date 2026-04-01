package transcendence.api42_service.services;

import jakarta.transaction.Transactional;
import lombok.RequiredArgsConstructor;
import me.tongfei.progressbar.ProgressBar;
import org.springframework.stereotype.Service;
import transcendence.api42_service.definition.curriculum.Pace;
import transcendence.api42_service.entities.PoolResult;
import transcendence.api42_service.entities.ProjectsUsers;
import transcendence.api42_service.entities.User;
import transcendence.api42_service.repositories.PoolResultRepository;
import transcendence.api42_service.repositories.ProjectsUsersRepository;
import transcendence.api42_service.repositories.UserRepository;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.*;
import java.util.logging.Logger;
import java.util.stream.Collectors;

@RequiredArgsConstructor
@Service
@Transactional
public class UserTalentPointCalculator  {
    private final UserRepository userRepository;
    private final ProjectsUsersRepository projectsUsersRepository;
    private final PoolResultRepository poolResultRepository;
    private final Logger logger;

    public void calculateUserTalentPoint() {
        logger.info("Calculate user performance point");
        List<User> activeUsers = Optional.ofNullable(userRepository.findByActiveTrueAndRankBetween(0, 6))
                .orElse(Collections.emptyList());
        List<ProjectsUsers> activeUsersProjectsUsers = Optional.ofNullable(projectsUsersRepository.findByUserIn(activeUsers))
                .orElse(Collections.emptyList());
        if (activeUsers.isEmpty()) {
            logger.warning("No active users between rank 0 and 6 found.");
            return;
        }

        try (ProgressBar pb = new ProgressBar("Calculating user Performance point", activeUsers.size())) {
            for (User user : activeUsers) {
                pb.step();
                try {
                    PoolResult poolResult = populatePoolResult(user, activeUsersProjectsUsers);
                    int poolScore = (calculatePoolCriteria(poolResult) * 20) / 100;
                    int paceScore = (calculatePaceCriteria(user) * 50) / 100;
                    int perfectionismScore = (calculatePerfectionismCriteria(user, activeUsersProjectsUsers) * 30) / 100;
                    user.setPerformanceScore(poolScore + paceScore + perfectionismScore);
                } catch (Exception e) {
                    logger.severe("Failed to calculate performance score for user " + user.getId() + ": " + e.getMessage());
                }
            }
        } catch (Exception e) {
            logger.severe("Failed to initialize progress bar: " + e.getMessage());
            return;
        }
        try {
            userRepository.saveAll(activeUsers);
        } catch (Exception e) {
            logger.severe("Failed to save user performance scores: " + e.getMessage());
        }
    }

    private PoolResult populatePoolResult(User user, List<ProjectsUsers> activeUsersProjectsUsers) {
        if (user == null || activeUsersProjectsUsers == null) {
            throw new IllegalArgumentException("User and activeUsersProjectsUsers cannot be null");
        }
        getLastedProjectsUsersBySlug(user, activeUsersProjectsUsers);
        Map<String, ProjectsUsers> lastedProjectsUsersBySlug = getLastedProjectsUsersBySlug(user, activeUsersProjectsUsers);
        PoolResult poolResult = poolResultRepository.findByUser(user)
                .orElseGet(() -> {
                    PoolResult newPoolResult = new PoolResult();
                    newPoolResult.setUser(user);
                    return newPoolResult;
                });
        poolResult.setC02Score(getProjectMaxScore("c-piscine-c-02", lastedProjectsUsersBySlug));
        poolResult.setC03Score(getProjectMaxScore("c-piscine-c-03", lastedProjectsUsersBySlug));
        poolResult.setC04Score(getProjectMaxScore("c-piscine-c-04", lastedProjectsUsersBySlug));
        poolResult.setC05Score(getProjectMaxScore("c-piscine-c-05", lastedProjectsUsersBySlug));
        poolResult.setC06Score(getProjectMaxScore("c-piscine-c-06", lastedProjectsUsersBySlug));
        poolResult.setC07Score(getProjectMaxScore("c-piscine-c-07", lastedProjectsUsersBySlug));
        poolResult.setC08Score(getProjectMaxScore("c-piscine-c-08", lastedProjectsUsersBySlug));
        poolResult.setC09Score(getProjectMaxScore("c-piscine-c-09", lastedProjectsUsersBySlug));
        poolResult.setC10Score(getProjectMaxScore("c-piscine-c-10", lastedProjectsUsersBySlug));
        poolResult.setExam0Score(getProjectMaxScore("c-piscine-exam-00", lastedProjectsUsersBySlug));
        poolResult.setExam1Score(getProjectMaxScore("c-piscine-exam-01", lastedProjectsUsersBySlug));
        poolResult.setExam2Score(getProjectMaxScore("c-piscine-exam-02", lastedProjectsUsersBySlug));
        poolResult.setExam3Score(getProjectMaxScore("c-piscine-final-exam", lastedProjectsUsersBySlug));
        try {
            poolResultRepository.save(poolResult);
        } catch (Exception e) {
            logger.severe("Failed to save PoolResult for user " + user.getId() + ": " + e.getMessage());
        }
        return poolResult;
    }

    public static Map<String, ProjectsUsers> getLastedProjectsUsersBySlug(User user, List<ProjectsUsers> activeUsersProjectsUsers) {
        if (user == null || activeUsersProjectsUsers == null) {
            return Collections.emptyMap();
        }
        List<ProjectsUsers> usersProjectsUsers = activeUsersProjectsUsers.stream()
                .filter(pu -> pu != null && pu.getUser() != null && pu.getUser().equals(user))
                .toList();
        return usersProjectsUsers.stream()
                .filter(pu -> pu.getProject() != null && pu.getProject().getSlug() != null)
                .collect(Collectors.toMap(
                        projectsUsers -> projectsUsers.getProject().getSlug(),
                        projectsUsers -> projectsUsers,
                        (a, b) -> a.getMarkedAt().isAfter(b.getMarkedAt()) ? a : b));
    }

    private int getProjectMaxScore(String project, Map<String, ProjectsUsers> lastedProjectsUsersBySlug) {
        if (lastedProjectsUsersBySlug == null || project == null) {
            return 0;
        }
        ProjectsUsers projectsUsers = lastedProjectsUsersBySlug.get(project);
        if (projectsUsers != null && projectsUsers.getFinalMark() != null) {
            return projectsUsers.getFinalMark();
        }
        return 0;
    }

    private int calculatePoolCriteria(PoolResult poolResult) {
        return calculatePoolExamScore(poolResult)
                        + calculatePoolProjectPassedScore(poolResult)
                        + calculatePoolProjectMaxScore(poolResult);
    }

    private int calculatePoolExamScore(PoolResult poolResult) {
        int[] poolExamScores = {
                poolResult.getExam0Score(),
                poolResult.getExam1Score(),
                poolResult.getExam2Score(),
                poolResult.getExam3Score()
        };
        int totalExam = 0;
        int sum = 0;
        for (int score : poolExamScores) {
            if (score > 0) {
                totalExam++;
                sum += score;
            }
        }
        return totalExam > 0 ? (int) (((double) sum / totalExam) * 50) / 100 : 0;
    }

    private int calculatePoolProjectPassedScore(PoolResult poolResult) {
        if (poolResult == null) {
            return 0;
        }
        List<AbstractMap.SimpleEntry<Integer, Integer>> poolProjectScores = new ArrayList<>();
        poolProjectScores.add(new AbstractMap.SimpleEntry<>(5, poolResult.getC02Score()));
        poolProjectScores.add(new AbstractMap.SimpleEntry<>(5, poolResult.getC03Score()));
        poolProjectScores.add(new AbstractMap.SimpleEntry<>(5, poolResult.getC04Score()));
        poolProjectScores.add(new AbstractMap.SimpleEntry<>(5, poolResult.getC05Score()));
        poolProjectScores.add(new AbstractMap.SimpleEntry<>(10, poolResult.getC06Score()));
        poolProjectScores.add(new AbstractMap.SimpleEntry<>(15, poolResult.getC07Score()));
        poolProjectScores.add(new AbstractMap.SimpleEntry<>(15, poolResult.getC08Score()));
        poolProjectScores.add(new AbstractMap.SimpleEntry<>(20, poolResult.getC09Score()));
        poolProjectScores.add(new AbstractMap.SimpleEntry<>(20, poolResult.getC10Score()));
        int sum = 0;
        for (AbstractMap.SimpleEntry<Integer, Integer> project : poolProjectScores) {
            if (project.getValue() >= 50) {
                sum += project.getKey();
            }
        }
        return (int) ((double) sum * 30) / 100;
    }

    private int calculatePoolProjectMaxScore(PoolResult poolResult) {
        if (poolResult == null) {
            return 0;
        }
        int[] projectScore = {
                poolResult.getC02Score(),
                poolResult.getC03Score(),
                poolResult.getC04Score(),
                poolResult.getC05Score(),
                poolResult.getC06Score(),
                poolResult.getC07Score(),
                poolResult.getC08Score(),
                poolResult.getC09Score(),
                poolResult.getC10Score()
        };
        int sum = 0;
        int totalPassed = 0;
        for (int score : projectScore) {
            if (score < 50)
                continue;
            else if (score < 60)
                sum += 50;
            else if (score < 70)
                sum += 55;
            else if (score < 80)
                sum += 60;
            else if (score < 90)
                sum += 70;
            else if (score < 100)
                sum += 80;
            else
                sum += 100;
            totalPassed++;
        }
        return totalPassed > 0 ? (int) (((double) sum / totalPassed) * 20) / 100 : 0;
    }

    private int calculatePaceCriteria(User user) {
        if (user == null) {
            throw new IllegalArgumentException("User cannot be null");
        }
        int userRank = user.getRank();
        long daysExpectedToReachCurrentProgress = calculateDaysExpectedToReachCurrentProgress(user, userRank);

        try {
            LocalDate startDate = LocalDate.of(Integer.parseInt(user.getPoolYear()), 10, 1);
            LocalDate currentDate = LocalDate.now();
            long daysActualToReachCurrentProgress = ChronoUnit.DAYS.between(startDate, currentDate) - user.getFreezeDays();
            int baseScore;
            if (daysActualToReachCurrentProgress > daysExpectedToReachCurrentProgress) {
                long daysBehind = daysActualToReachCurrentProgress - daysExpectedToReachCurrentProgress;
                long maxAllowedDaysBehind = daysExpectedToReachCurrentProgress / 2;
                if (daysBehind >= maxAllowedDaysBehind) {
                    baseScore = 0;
                } else {
                    baseScore = 50 - (int) (((double) daysBehind / maxAllowedDaysBehind) * 50);
                }
            } else if (daysActualToReachCurrentProgress < daysExpectedToReachCurrentProgress) {
                long daysAhead = daysExpectedToReachCurrentProgress - daysActualToReachCurrentProgress;
                long maxAllowedDaysAhead = daysExpectedToReachCurrentProgress / 2;
                if (daysAhead >= maxAllowedDaysAhead) {
                    baseScore = 100;
                } else {
                    baseScore = 50 + (int) (((double) daysAhead / maxAllowedDaysAhead) * 50);
                }
            } else {
                baseScore = 50;
            }
            return baseScore;
        } catch (Exception e) {
            logger.severe("Failed to calculate pace criteria for user " + user.getId() + ": " + e.getMessage());
            return 0;
        }
    }

    private long calculateDaysExpectedToReachCurrentProgress(User user, int userRank) {
        if (user == null) {
            throw new IllegalArgumentException("User cannot be null");
        }
        int userRankScore =  user.getRankProgressPercent();
        long daysExpectedFinishPreviousRank = 0;
        if (userRank > 0) {
            daysExpectedFinishPreviousRank = Pace.getDaysToFinishRankAccumulation(user.getRank() - 1);
        }
        long daysExpectedToReachCurrentProgress;
        if (userRankScore > 0) {
            daysExpectedToReachCurrentProgress = daysExpectedFinishPreviousRank + ((Pace.getDaysToFinishRank(userRank) * userRankScore) / 100);
        } else {
            daysExpectedToReachCurrentProgress = daysExpectedFinishPreviousRank;
        }
        return daysExpectedToReachCurrentProgress;
    }

    private static final Set<String> INVALID_PROJECTS = Set.of(
            "exam-rank-02",
            "exam-rank-03",
            "exam-rank-04",
            "exam-rank-05",
            "exam-rank-06",
            "cpp-module-00",
            "cpp-module-01",
            "cpp-module-02",
            "cpp-module-03",
            "cpp-module-04",
            "cpp-module-05",
            "cpp-module-06",
            "cpp-module-07",
            "cpp-module-08",
            "cpp-module-09",
            "netpractice",
            "42_collaborative_resume"
    );

    public int calculatePerfectionismCriteria(User user, List<ProjectsUsers> activeUsersProjectsUsers) {
        if (user == null || activeUsersProjectsUsers == null) {
            return 0;
        }
        Map<String, ProjectsUsers> lastedProjectsUsersBySlug = getLastedProjectsUsersBySlug(user, activeUsersProjectsUsers);
        Set<String> finishedProjects = Optional.ofNullable(user.getFinishedProjects())
                .orElse(Collections.emptySet());
        int actualBonusScore = 0;
        int maxBonusScore = 0;
        for (String project : finishedProjects) {
            if (INVALID_PROJECTS.contains(project)) {
                continue;
            }
            int score = getProjectMaxScore(project, lastedProjectsUsersBySlug);
            if (score > 100 && score < 125) {
                actualBonusScore += 1;
            } else if (score >= 125) {
                actualBonusScore += 2;
            }
            maxBonusScore += 2;
        }
        return (int) (((double) actualBonusScore / maxBonusScore) * 100);
    }
}