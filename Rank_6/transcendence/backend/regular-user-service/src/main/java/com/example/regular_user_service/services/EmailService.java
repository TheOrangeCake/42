package com.example.regular_user_service.services;

import com.example.regular_user_service.config.EmailConfig;
import lombok.RequiredArgsConstructor;
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.mail.SimpleMailMessage;
import org.springframework.mail.javamail.JavaMailSender;
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
@EnableConfigurationProperties(EmailConfig.class)
public class EmailService {
    private final JavaMailSender javaMailSender;
    private final EmailConfig emailConfig;

    @Async
    public void sendEmail(String toMail, String subject, String messageBody) {
        final var simpleMailMessage = new SimpleMailMessage();
        simpleMailMessage.setFrom(emailConfig.getUsername());
        simpleMailMessage.setTo(toMail);
        simpleMailMessage.setSubject(subject);
        simpleMailMessage.setText(messageBody);
        javaMailSender.send(simpleMailMessage);
    }
}
