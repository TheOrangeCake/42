package transcendence.api42_service.repositories.specification;

import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Component;
import transcendence.api42_service.entities.Campus;

@Component
public final class CampusSpecifications {
	public static Specification<Campus> hasName(String name) {
		return (root, query, cb) ->
				name == null ? null : cb.equal(root.get("name"), name);
	}

	public static Specification<Campus> hasCountry(String country) {
		return (root, query, cb) ->
				country == null ? null : cb.equal(root.get("country"), country);
	}

	public static Specification<Campus> hasCity(String city) {
		return (root, query, cb) ->
				city == null ? null : cb.equal(root.get("city"), city);
	}
}
