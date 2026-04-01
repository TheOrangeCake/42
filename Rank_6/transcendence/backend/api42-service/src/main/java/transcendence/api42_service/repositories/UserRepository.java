package transcendence.api42_service.repositories;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import transcendence.api42_service.entities.User;

import java.util.List;
import java.util.Optional;

public interface UserRepository extends JpaRepository<User, Long>, JpaSpecificationExecutor<User> {
	List<User> findByActiveTrue();
	List<User> findByActiveTrueAndRankBetween(int minRank, int maxRank);
	Page<User> findByLastName(String lastName, Pageable pageable);
	Page<User> findByFirstName(String firstName, Pageable pageable);
	List<User> findByLoginContainingIgnoreCase(String login);
	Optional<User> findByLogin(String login);
}