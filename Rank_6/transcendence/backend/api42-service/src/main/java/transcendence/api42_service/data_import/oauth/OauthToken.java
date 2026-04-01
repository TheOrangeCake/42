package transcendence.api42_service.data_import.oauth;

import org.springframework.stereotype.Component;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
@Component
public final class OauthToken {
	@JsonProperty("access_token")
	private String accessToken;

	@JsonProperty("expires_in")
	private String expiresIn;

	@JsonProperty("created_at")
	private String createdAt;

	@JsonProperty("secret_valid_until")
	private int secretValidUntil;
}