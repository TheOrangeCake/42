package transcendence.api42_service.dto.mapper;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;
import transcendence.api42_service.dto.CampusDto;
import transcendence.api42_service.entities.Campus;
import transcendence.api42_service.repositories.CampusRepository;

import java.util.Optional;

@RequiredArgsConstructor
@Component
public final class CampusMapper {
	private final CampusRepository campusRepository;

	public CampusDto mapToDto(Campus campus) {
		if (campus == null) {
			return null;
		}
		return new CampusDto(
				campus.getId(),
				campus.getName(),
				campus.getTimeZone(),
				campus.getUsersCount(),
				campus.getCountry(),
				campus.getAddress(),
				campus.getZip(),
				campus.getCity(),
				campus.getWebsite(),
				campus.getFacebook(),
				campus.getTwitter(),
				campus.getActive(),
				campus.getPublicCampus(),
				campus.getEmailExtension()
		);
	}

	public Campus mapToCampus(CampusDto dto) {
		if (dto == null) {
			return null;
		}
		Campus campus;
		Optional<Campus> existingCampus = campusRepository.findByName(dto.name());
		if (existingCampus.isPresent()) {
			campus = populateCampus(existingCampus.get(), dto);
		} else {
			campus = new Campus();
            populateCampus(campus, dto);
        }

		return campus;
	}

	private Campus populateCampus(Campus campus, CampusDto dto) {
		campus.setId(dto.id());
		campus.setName(dto.name());
		campus.setTimeZone(dto.time_zone());
		campus.setUsersCount(dto.users_count());
		campus.setCountry(dto.country());
		campus.setAddress(dto.address());
		campus.setZip(dto.zip());
		campus.setCity(dto.city());
		campus.setWebsite(dto.website());
		campus.setFacebook(dto.facebook());
		campus.setTwitter(dto.twitter());
		campus.setActive(dto.active());
		campus.setPublicCampus(dto.publicCampus());
		campus.setEmailExtension(dto.email_extension());
		return campus;
	}
}
