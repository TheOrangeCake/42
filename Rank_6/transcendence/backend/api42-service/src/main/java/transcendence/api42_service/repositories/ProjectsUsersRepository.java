package transcendence.api42_service.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import transcendence.api42_service.entities.ProjectsUsers;
import transcendence.api42_service.entities.User;

import java.util.List;

public interface ProjectsUsersRepository extends JpaRepository<ProjectsUsers, Long> {
	List<ProjectsUsers> findByUserIn(List<User> activeUsers);
}