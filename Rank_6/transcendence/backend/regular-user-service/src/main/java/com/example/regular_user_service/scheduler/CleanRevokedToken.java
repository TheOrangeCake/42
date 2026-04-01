package com.example.regular_user_service.scheduler;

import com.example.regular_user_service.repositories.RevokeTokenRepository;
import jakarta.transaction.Transactional;
import lombok.RequiredArgsConstructor;
import org.springframework.context.annotation.Configuration;
import org.springframework.scheduling.annotation.EnableScheduling;
import org.springframework.scheduling.annotation.Scheduled;

import java.util.Date;
import java.util.logging.Logger;

@Configuration
@EnableScheduling
@RequiredArgsConstructor
public class CleanRevokedToken {
    private final RevokeTokenRepository revokedTokenRepository;
    private final Logger logger;

    @Scheduled(fixedDelay = (60 * 60 * 1000))
    @Transactional
    public void cleanRevokedToken() {
        logger.info("Start cleaning Revoked Token Database");
        Date accessTokenCutOff = new Date(System.currentTimeMillis() - (15 * 60 * 1000));
        Date refreshTokenCutOff = new Date(System.currentTimeMillis() - (7 * 24 * 60 * 60 * 1000));
        revokedTokenRepository.deleteByTypeAndRevokedAtBefore("access token", accessTokenCutOff);
        revokedTokenRepository.deleteByTypeAndRevokedAtBefore("refresh token", refreshTokenCutOff);
        logger.info("Revoked Token Database cleaned.");
    }
}