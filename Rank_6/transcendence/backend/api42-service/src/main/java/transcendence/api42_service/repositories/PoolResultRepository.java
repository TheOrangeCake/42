package transcendence.api42_service.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import transcendence.api42_service.entities.PoolResult;
import transcendence.api42_service.entities.User;

import java.util.Optional;

public interface PoolResultRepository extends JpaRepository<PoolResult, Long> {
    Optional<PoolResult> findByUser(User user);
}