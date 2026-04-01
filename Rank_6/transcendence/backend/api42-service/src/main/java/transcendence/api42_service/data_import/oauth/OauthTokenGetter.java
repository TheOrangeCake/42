package transcendence.api42_service.data_import.oauth;

import lombok.Getter;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpStatusCode;
import org.springframework.http.MediaType;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestClient;
import transcendence.api42_service.exception.ApiCallFailException;
import transcendence.api42_service.exception.InvalidTokenException;

@Getter
@RequiredArgsConstructor
@Service
public class OauthTokenGetter {
    private volatile String token;
    private final RestClient restClient;
    private OauthToken oauthToken;

    @Value("${api42.secret}")
    private String apiSecret;

    // Currently not in use.
    // The challenge is the env secret is needed to be updated manually.
    // So a system to trigger a secret reload need to be implemented.
    @Value("${api42.next-secret")
    private String apiNextSecret;

    @Value("${api42.uid}")
    private String apiUID;

    public synchronized void retrieveToken() {
        oauthToken = restClient.post()
                .uri("oauth/token")
                .contentType(MediaType.APPLICATION_FORM_URLENCODED)
                .body("grant_type=client_credentials" +
                        "&client_id=" + apiUID +
                        "&client_secret=" + apiSecret)
                .accept(MediaType.APPLICATION_JSON)
                .retrieve()
                .onStatus(HttpStatusCode::isError, ((request, response) -> {
                    throw new ApiCallFailException(response.getStatusCode());
                }))
                .body(OauthToken.class);
        if (oauthToken == null || oauthToken.getAccessToken() == null) {
            throw new InvalidTokenException();
        }
        token = oauthToken.getAccessToken();
    }
}