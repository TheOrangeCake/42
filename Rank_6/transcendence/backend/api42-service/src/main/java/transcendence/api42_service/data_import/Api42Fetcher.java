package transcendence.api42_service.data_import;

import lombok.AllArgsConstructor;
import org.springframework.core.ParameterizedTypeReference;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatusCode;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestClient;
import org.springframework.web.util.UriComponentsBuilder;
import transcendence.api42_service.dto.CampusDto;
import transcendence.api42_service.dto.PageResult;
import transcendence.api42_service.dto.ProjectsUsersRequestDto;
import transcendence.api42_service.dto.UserRequestDto;
import transcendence.api42_service.exception.ApiCallFailException;

import java.net.URI;
import java.util.List;

@AllArgsConstructor
@Service
public class Api42Fetcher {
    private final RestClient restClient;

    private <T> PageResult<T> fetch(
            String token,
            URI uri,
            ParameterizedTypeReference<List<T>> responseType
    ) {
        ResponseEntity<List<T>> response = restClient.get()
                .uri(uri)
                .header("Authorization", "Bearer " + token)
                .accept(MediaType.APPLICATION_JSON)
                .retrieve()
                .onStatus(HttpStatusCode::isError, (request, res) -> {
                    throw new ApiCallFailException(res.getStatusCode());
                })
                .toEntity(responseType);
        boolean hasNext = hasNextPage(response.getHeaders());
        int xTotal = getXTotal(response.getHeaders());

        return new PageResult<>(response.getBody(), hasNext, xTotal);
    }

    public PageResult<CampusDto> fetchCampusDtoData(String token, int page, int perPage) {
        URI uri = UriComponentsBuilder.fromPath("v2/campus")
                .queryParam("page", page)
                .queryParam("per_page", perPage)
                .queryParam("filter[active]", "true")
                .queryParam("filter[public]", "true")
                .build()
                .toUri();
        return fetch(token, uri, new ParameterizedTypeReference<>() {});
    }

    public PageResult<UserRequestDto> fetchUserDtoData(String token, int page, int perPage, Long id) {
        URI uri = UriComponentsBuilder.fromPath("v2/users")
                .queryParam("page", page)
                .queryParam("per_page", perPage)
                .queryParam("filter[kind]", "student")
                .queryParam("filter[alumni?]", "false")
                .queryParam("filter[primary_campus_id]", id.toString())
                .build()
                .toUri();
        return fetch(token, uri, new ParameterizedTypeReference<>() {});
    }

    public PageResult<ProjectsUsersRequestDto> fetchProjectsUsersDtoData(String token, int page, int perPage, Long id, int cursusId, Long campusId) {
        URI uri = UriComponentsBuilder.fromPath("v2/users/{id}/projects_users")
                .queryParam("page", page)
                .queryParam("per_page", perPage)
                .queryParam("filter[cursus]", cursusId)
                .queryParam("filter[campus]", campusId)
                .build(id);
        return fetch(token, uri, new ParameterizedTypeReference<>() {});
    }

    private boolean hasNextPage(HttpHeaders headers) {
        List<String> links = headers.get(HttpHeaders.LINK);
        if (links == null) {
            return false;
        }
        return links.stream().anyMatch(link -> link.contains("rel=\"next\""));
    }

    private int getXTotal(HttpHeaders headers) {
        String xTotal = headers.getFirst("X-Total");
        if (xTotal == null) {
            return -1;
        }
        return Integer.parseInt(xTotal);
    }

}