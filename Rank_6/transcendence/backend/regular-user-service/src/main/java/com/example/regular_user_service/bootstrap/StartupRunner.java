package com.example.regular_user_service.bootstrap;

import lombok.RequiredArgsConstructor;
import org.jspecify.annotations.NonNull;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import java.util.logging.Logger;

@Component
@RequiredArgsConstructor
public class StartupRunner implements CommandLineRunner {
    private final Logger logger;

    @Override
    public void run(String @NonNull ... args){
        System.out.println("""
                         _____             _            _____                _____             _         \s
                        | __  |___ ___ _ _| |___ ___   |  |  |___ ___ ___   |   __|___ ___ _ _|_|___ ___ \s
                        |    -| -_| . | | | | .'|  _|  |  |  |_ -| -_|  _|  |__   | -_|  _| | | |  _| -_|
                        |__|__|___|_  |___|_|__,|_|    |_____|___|___|_|    |_____|___|_|  \\_/|_|___|___|
                                  |___|                                                                  \s"""
        );
        logger.info("Service is used to manage regular users (not from 42). By Nguyen NGUYEN (hoannguy).");
    }
}
