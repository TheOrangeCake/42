package transcendence.api42_service.exception;

public class BadTokenException extends RuntimeException{
	public BadTokenException(String error) {
		super(error);
	}
}