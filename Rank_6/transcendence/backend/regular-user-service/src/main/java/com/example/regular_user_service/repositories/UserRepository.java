package com.example.regular_user_service.repositories;

import com.example.regular_user_service.entities.User;
import lombok.NonNull;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface UserRepository extends JpaRepository<User, Long> {
	Optional<User> findUserById(Long id);
	Optional<User> findUserByEmailOrUsername(String email, String username);
	boolean existsByEmail(String email);
    Optional<User> findUserByEmail(String email);
}