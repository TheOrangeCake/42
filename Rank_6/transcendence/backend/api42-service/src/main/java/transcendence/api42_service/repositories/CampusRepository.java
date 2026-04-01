package transcendence.api42_service.repositories;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import transcendence.api42_service.entities.Campus;

import java.util.Optional;

public interface CampusRepository extends JpaRepository<Campus, Long>, JpaSpecificationExecutor<Campus> {
	Optional<Campus> findByName(String name);
	Page<Campus> findByName(String name, Pageable pageable);
}