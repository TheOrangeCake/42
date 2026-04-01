package transcendence.api42_service.data_import.interfaces;

import transcendence.api42_service.dto.PageResult;
import transcendence.api42_service.exception.ApiCallFailException;

@FunctionalInterface
public interface PageFetcherInterface<T> {
	PageResult<T> fetch(String token, int page, int resultPerPage) throws ApiCallFailException;
}

