package transcendence.api42_service.exception;

public class NoCommonCoreException extends RuntimeException {
	public NoCommonCoreException() {
		super("No Common Core. User may not be active.");
	}
}