package transcendence.api42_service.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import transcendence.api42_service.entities.Project;

import java.util.List;

public interface ProjectRepository extends JpaRepository<Project, Long> {
	List<Project> findByRankGreaterThanEqual(Integer rank);
}