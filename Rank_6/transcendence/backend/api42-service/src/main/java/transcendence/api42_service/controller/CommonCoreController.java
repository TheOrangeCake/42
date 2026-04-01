package transcendence.api42_service.controller;

import lombok.AllArgsConstructor;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import transcendence.api42_service.definition.curriculum.CommonCoreCurriculum;
import transcendence.api42_service.dto.CommonCoreDto;
import transcendence.api42_service.dto.mapper.CommonCoreMapper;
import transcendence.api42_service.repositories.ProjectRepository;


@RequestMapping("v1/api42/commoncore")
@AllArgsConstructor
@RestController
public class CommonCoreController {
	private final ProjectRepository projectRepository;
	private final CommonCoreMapper commonCoreMapper;

	@GetMapping()
	public CommonCoreDto commonCore() {
		return commonCoreMapper.mapToDto(CommonCoreCurriculum.RANKS, projectRepository);
	}

}