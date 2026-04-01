package transcendence.api42_service.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.client.RestClient;

@Configuration
public class Api42Config {

    @Bean
    public RestClient tokenClient() {
        return RestClient.builder()
                .baseUrl("https://api.intra.42.fr")
                .build();
    }

}