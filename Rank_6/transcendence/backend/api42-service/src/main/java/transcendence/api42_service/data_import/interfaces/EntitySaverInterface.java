package transcendence.api42_service.data_import.interfaces;

import java.util.List;

@FunctionalInterface
public interface EntitySaverInterface<T> {
	void save(List<T> entities);
}