package transcendence.api42_service.dto.mapper;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;
import tools.jackson.databind.ObjectMapper;
import transcendence.api42_service.definition.project.UserCommonCore;
import transcendence.api42_service.dto.*;
import transcendence.api42_service.entities.Campus;
import transcendence.api42_service.entities.User;
import transcendence.api42_service.exception.NoCommonCoreException;
import transcendence.api42_service.repositories.UserRepository;

import java.util.Optional;
import java.util.logging.Logger;

@RequiredArgsConstructor
@Component
public final class UserMapper {
	private final EnvVariables envVariables;
	private final UserRepository userRepository;
	private final Logger logger;

	public UserSimpleResponseDto mapToSimpleDto(User user) {
		if (user == null) {
			return null;
		}
		return new UserSimpleResponseDto(
				user.getId(),
				user.getLogin(),
				user.getFirstName(),
				user.getLastName(),
				user.getIntraUrl(),
				createCustomAvatarUrl(user),
				mapAvatar(user),
				user.getPoolMonth(),
				user.getPoolYear(),
				user.getRank(),
				user.getRankProgressPercent(),
				user.getPerformanceScore(),
				user.getLfg()
		);
	}

	@SuppressWarnings("ReassignedVariable")
	public UserDetailedResponseDto mapToDetailedDto(User user) {
		if (user == null) {
			return null;
		}
		UserCommonCore userCommonCore = null;
		try {
			userCommonCore = fromJson(user.getDetailedProfileJson());
		} catch (NoCommonCoreException e) {
			logger.warning("Invalid UserCommonCore JSON. " + e);
		}
		return new UserDetailedResponseDto(
				user.getId(),
				user.getCampus().getName(),
				user.getEmail(),
				user.getLogin(),
				user.getFirstName(),
				user.getLastName(),
				user.getIntraUrl(),
				createCustomAvatarUrl(user),
				createCustomBannerUrl(user),
				mapAvatar(user),
				user.getPoolMonth(),
				user.getPoolYear(),
				user.getAlumni(),
				user.getActive(),
				user.getRank(),
				user.getRankProgressPercent(),
				user.getPerformanceScore(),
				user.getLfg(),
				user.getFinishedProjects(),
				user.getEligibleProjects(),
				userCommonCore
		);
	}

	public User mapRequestToUser(UserRequestDto dto, Campus campus) {
		if (dto == null) {
			return null;
		}
		User user;
		Optional<User> existingUser = userRepository.findById(dto.id());
		if (existingUser.isPresent()) {
            user = populateUser(existingUser.get(), dto, campus);
        } else {
			user = new User();
			populateUser(user, dto, campus);
			user.setId(dto.id());
			user.setEmail(dto.email());
			user.setLogin(dto.login());
			setIntraURl(user, dto.login());
			user.setCustomAvatarUrl(null);
			user.setCustomBannerUrl(envVariables.getDefaultBanner());
			user.setCreatedAt(dto.created_at());
			user.setRank(null);
			user.setFreezeDays(null);
			user.setRankProgressPercent(null);
			user.setPerformanceScore(null);
			user.setFinishedProjects(null);
			user.setEligibleProjects(null);
			user.setDetailedProfileJson(null);
			user.setPoolResult(null);
		}

		return user;
	}

	private User populateUser(User user, UserRequestDto dto, Campus campus) {
		user.setCampus(campus);
		user.setFirstName(dto.first_name());
		user.setLastName(dto.last_name());
		user.setPoolMonth(dto.pool_month());
		user.setPoolYear(dto.pool_year());
		user.setUpdatedAt(dto.updated_at());
		user.setAlumni(dto.alumni());
		user.setActive(dto.active());
		if (dto.image() != null) {
			user.setImageLink(dto.image().link());

			if (dto.image().versions() != null) {
				user.setImageLarge(dto.image().versions().large());
				user.setImageMedium(dto.image().versions().medium());
				user.setImageSmall(dto.image().versions().small());
				user.setImageMicro(dto.image().versions().micro());
			} else {
				user.setImageLarge(dto.image().link());
				user.setImageMedium(dto.image().link());
				user.setImageSmall(dto.image().link());
				user.setImageMicro(dto.image().link());
			}
		} else {
			user.setImageLink(envVariables.getImageDomain() + envVariables.getDefaultAvatar());
			user.setImageLarge(envVariables.getImageDomain() + envVariables.getDefaultAvatar());
			user.setImageMedium(envVariables.getImageDomain() + envVariables.getDefaultAvatar());
			user.setImageSmall(envVariables.getImageDomain() + envVariables.getDefaultAvatar());
			user.setImageMicro(envVariables.getImageDomain() + envVariables.getDefaultAvatar());
		}
		return user;
	}

	private AvatarDto mapAvatar(User user) {
		AvatarVersionsDto versions = new AvatarVersionsDto(
				user.getImageLarge(),
				user.getImageMedium(),
				user.getImageSmall(),
				user.getImageMicro()
		);
		return new AvatarDto(
				user.getImageLink(),
				versions
		);
	}

	private final ObjectMapper OBJECT_MAPPER = new ObjectMapper();

	private UserCommonCore fromJson(String json) {
		try {
			return OBJECT_MAPPER.readValue(json, UserCommonCore.class);
		} catch (Exception e) {
			throw new NoCommonCoreException();
		}
	}

	private void setIntraURl(User user, String login) {
		String baseUrl = "https://intra.42.fr/users/";
		user.setIntraUrl(baseUrl + login);
	}

	private String createCustomBannerUrl(User user) {
		return envVariables.getImageDomain() + user.getCustomBannerUrl();
	}

	private String createCustomAvatarUrl(User user) {
		String customAvatar = user.getCustomAvatarUrl();
		return customAvatar != null ? envVariables.getImageDomain() + customAvatar : null;
	}
}