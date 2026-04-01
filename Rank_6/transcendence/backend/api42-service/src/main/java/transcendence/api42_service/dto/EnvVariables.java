package transcendence.api42_service.dto;

import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Getter
@Component
public class EnvVariables {
    @Value("${api42.default-banner}")
    private String defaultBanner;

    @Value("${api42.default-avatar}")
    private String defaultAvatar;

    @Value("${api42.image-domain}")
    private String imageDomain;

    @Value("${api42.upload-location}")
    private String uploadDir;
}