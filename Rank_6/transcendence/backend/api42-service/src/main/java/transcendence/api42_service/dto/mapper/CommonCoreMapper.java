package transcendence.api42_service.dto.mapper;

import lombok.AllArgsConstructor;
import org.springframework.stereotype.Component;
import transcendence.api42_service.definition.curriculum.RankDefinition;
import transcendence.api42_service.dto.CommonCoreDto;
import transcendence.api42_service.dto.CommonCoreRankDto;
import transcendence.api42_service.dto.ProjectResponseDto;
import transcendence.api42_service.entities.Project;
import transcendence.api42_service.repositories.ProjectRepository;

import java.util.List;
import java.util.Map;
import java.util.SortedMap;
import java.util.TreeMap;

@AllArgsConstructor
@Component
public final class CommonCoreMapper {
	private final ProjectMapper projectMapper;

	public CommonCoreDto mapToDto(
			SortedMap<Integer, RankDefinition> curriculum,
			ProjectRepository projectRepository
	) {
		SortedMap<Integer, CommonCoreRankDto> ranks = new TreeMap<>();
		for (Map.Entry<Integer, RankDefinition> rank : curriculum.entrySet()) {
			Integer rankNumber = rank.getKey();
			RankDefinition rankDefinition = rank.getValue();
			CommonCoreRankDto rankDto = new CommonCoreRankDto(rankDefinition.mandatory(), rankDefinition.choices());
			ranks.put(rankNumber, rankDto);
		}
		List<Project> projects = projectRepository.findByRankGreaterThanEqual(0);
		List<ProjectResponseDto> projectResponseDto = projects
				.stream()
				.map(projectMapper::mapToResponseDto).toList();
		return new CommonCoreDto(projectResponseDto, ranks);
	}
}