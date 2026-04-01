package transcendence.api42_service.exception;

import lombok.Getter;
import org.springframework.http.HttpStatusCode;

@Getter
public class ApiCallFailException extends RuntimeException {
    private final HttpStatusCode status;

    public ApiCallFailException(HttpStatusCode status) {
        super(status.toString());
        this.status = status;
    }
}