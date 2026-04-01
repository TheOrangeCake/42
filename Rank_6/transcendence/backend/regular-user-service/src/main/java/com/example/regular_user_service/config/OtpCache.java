package com.example.regular_user_service.config;

import com.google.common.cache.CacheBuilder;
import com.google.common.cache.CacheLoader;
import com.google.common.cache.LoadingCache;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.concurrent.TimeUnit;

@Configuration
public class OtpCache {

    @Bean
    public LoadingCache<String, Integer> optCache() {
        int expirationMinutes = 5;
        return CacheBuilder.newBuilder()
                .expireAfterWrite(expirationMinutes, TimeUnit.MINUTES)
                .build(new CacheLoader<>() {
                    @Override
                    public Integer load(String key) {
                        return 0;
                    }
                });
    }
}