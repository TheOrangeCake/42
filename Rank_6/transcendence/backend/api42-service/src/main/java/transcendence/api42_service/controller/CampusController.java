package transcendence.api42_service.controller;

import lombok.AllArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.data.web.PageableDefault;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;
import transcendence.api42_service.repositories.specification.CampusSpecifications;
import transcendence.api42_service.dto.CampusDto;
import transcendence.api42_service.dto.mapper.CampusMapper;
import transcendence.api42_service.entities.Campus;
import transcendence.api42_service.repositories.CampusRepository;

import java.util.Set;
import java.util.stream.Collectors;

@RequestMapping("v1/api42/campuses")
@AllArgsConstructor
@RestController
public class CampusController {
	private final CampusRepository campusRepository;
	private final CampusMapper campusMapper;

	private static final Set<String> ALL_CAMPUSES_ALLOWED_SORTS = Set.of(
			"name",
			"country",
			"city",
			"usersCount"
	);

	@GetMapping()
	public Page<CampusDto> getCampuses(
			@RequestParam(required = false) String name,
			@RequestParam(required = false) String country,
			@RequestParam(required = false) String city,
			@PageableDefault(size = 25) Pageable pageable) {
		int maxSize = 50;
		Sort sort = pageable
				.getSort()
				.stream()
				.filter(order -> ALL_CAMPUSES_ALLOWED_SORTS.contains(order.getProperty()))
				.collect(Collectors.collectingAndThen(
						Collectors.toList(),
						orders -> orders.isEmpty()
								? Sort.by("usersCount")
								: Sort.by(orders)
				));
		Pageable safePageable = PageRequest.of(
				pageable.getPageNumber(),
				Math.min(pageable.getPageSize(), maxSize),
				sort);
		Specification<Campus> spec = Specification
				.where(CampusSpecifications.hasName(name))
				.and(CampusSpecifications.hasCountry(country))
				.and(CampusSpecifications.hasCity(city));
		return campusRepository.findAll(spec, safePageable)
				.map(campusMapper::mapToDto);
	}

	@GetMapping("/id/{id}")
	public CampusDto getCampusById(@PathVariable Long id) {
		if (id == null) {
			throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Campus ID cannot be null");
		}
		Campus campus = campusRepository.findById(id)
				.orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND, "Campus " + id + " not found with ID"));
		return campusMapper.mapToDto(campus);
	}

	@GetMapping("/name/{name}")
	public Page<CampusDto> getCampusesByName(
			@PathVariable String name,
			@PageableDefault(size = 25) Pageable pageable) {
		if (name == null || name.trim().isEmpty()) {
			throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Campus name cannot be null or empty");
		}
		int maxSize = 50;
		Pageable safePageable = PageRequest.of(
				pageable.getPageNumber(),
				Math.min(pageable.getPageSize(), maxSize)
		);
		return campusRepository.findByName(name, safePageable)
				.map(campusMapper::mapToDto);
	}
}