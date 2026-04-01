package transcendence.api42_service.dto;

import com.fasterxml.jackson.annotation.JsonProperty;
import java.time.OffsetDateTime;

public record UserRequestDto(
        Long id,
        String campus,
        String email,
        String login,
        String first_name,
        String last_name,
        AvatarDto image,
        String pool_month,
        String pool_year,
        OffsetDateTime created_at,
        OffsetDateTime updated_at,
        @JsonProperty("alumni?")
        Boolean alumni,
        @JsonProperty("active?")
        Boolean active
    ) {}