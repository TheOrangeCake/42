package transcendence.api42_service.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.logging.Logger;

@Configuration
public class LoggerConfig {

    @Bean
    public Logger appLogger() {
        return Logger.getLogger("Api42 Service");
    }
}