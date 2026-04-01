package transcendence.api42_service.dto;

import java.util.List;
import java.util.function.Function;

public record PageResult<T>(List<T> items, boolean hasNext, int xTotal) {
	public <R> PageResult<R> mapItems(Function<T, R> mapper) {
		return new PageResult<>(
				items.stream().map(mapper).toList(),
				hasNext,
				xTotal
		);
	}
}
