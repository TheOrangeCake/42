package transcendence.api42_service.dto;

import transcendence.api42_service.definition.project.UserCommonCore;

import java.util.Set;

public record UserDetailedResponseDto(
		Long id,
        String campus,
        String email,
        String login,
        String first_name,
        String last_name,
        String intra_url,
		String custom_avatar_url,
		String custom_banner_url,
        AvatarDto image,
        String pool_month,
        String pool_year,
        Boolean alumni,
        Boolean active,
		Integer rank,
		Integer rank_progress_percent,
		Integer performance_score,
		String lfg,
		Set<String> finished_projects,
		Set<String> eligible_projects,
		UserCommonCore common_core
) {
}