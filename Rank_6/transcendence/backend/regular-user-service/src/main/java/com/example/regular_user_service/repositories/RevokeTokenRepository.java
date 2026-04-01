package com.example.regular_user_service.repositories;

import com.example.regular_user_service.entities.RevokedToken;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Date;

public interface RevokeTokenRepository extends JpaRepository<RevokedToken, String> {
    void deleteByTypeAndRevokedAtBefore(String type, Date revokedAtBefore);
}