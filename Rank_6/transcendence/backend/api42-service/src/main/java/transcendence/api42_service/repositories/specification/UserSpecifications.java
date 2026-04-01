package transcendence.api42_service.repositories.specification;

import jakarta.persistence.criteria.Join;
import jakarta.persistence.criteria.JoinType;
import jakarta.persistence.criteria.Predicate;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Component;
import transcendence.api42_service.entities.Campus;
import transcendence.api42_service.entities.User;

import java.util.Set;

@Component
public final class UserSpecifications {
	public static Specification<User> isActive() {
		return (table, query, criteria) -> criteria.isTrue(table.get("active"));
	}

	public static Specification<User> betweenRank(int minRank, int maxRank) {
		return (table, query, criteria) ->
				criteria.between(table.get("rank"), minRank, maxRank);
	}

	public static Specification<User> searchByNameOrLogin(String search) {
		return (table, query, criteria) -> {
			if (search == null || search.isBlank() || search.trim().isEmpty()) {
				return null;
			}
			Predicate firstNamePredicate = criteria.like(criteria.lower(table.get("firstName")), "%" + search.toLowerCase() + "%");
			Predicate lastNamePredicate = criteria.like(criteria.lower(table.get("lastName")), "%" + search.toLowerCase() + "%");
			Predicate loginPredicate = criteria.like(criteria.lower(table.get("login")), "%" + search.toLowerCase() + "%");
			return criteria.or(firstNamePredicate, lastNamePredicate, loginPredicate);
		};
	}

	public static Specification<User> hasPoolMonth(String poolMonth) {
		return (table, query, criteria) ->
				poolMonth == null ? null : criteria.equal(table.get("poolMonth"), poolMonth);
	}

	public static Specification<User> hasPoolYear(String poolYear) {
		return (table, query, criteria) ->
				poolYear == null ? null : criteria.equal(table.get("poolYear"), poolYear);
	}

	public static Specification<User> hasCampusName(String campusName) {
		return (table, query, criteria) -> {
			if (campusName == null) {
				return null;
			}
			Join<User, Campus> campus = table.join("campus");
			return criteria.equal(campus.get("name"), campusName);
		};
	}

	public static Specification<User> hasRank(Integer rank) {
		return (table, query, criteria) ->
				rank == null ? null : criteria.equal(table.get("rank"), rank);
	}

	public static Specification<User> hasEligibleProject(String eligibleProject) {
		return (table, query, criteria) -> {
			if (eligibleProject == null) {
				return null;
			}
			Join<User, String> joinTable = table.joinSet("eligibleProjects", JoinType.INNER);
			return criteria.equal(joinTable, eligibleProject);
		};
	}

	public static Specification<User> performanceScoreBetween(Integer min, Integer max) {
		return (table, query, criteria) -> {
			if (min == null && max == null) {
				return null;
			}
			if ((min != null && min < 0) || (max != null && max > 100)) {
				return null;
			}
			if (min != null && max != null) {
				return criteria.between(table.get("performanceScore"), min, max);
			}
			if (min != null) {
				return criteria.greaterThanOrEqualTo(table.get("performanceScore"), min);
			}
			return criteria.lessThanOrEqualTo(table.get("performanceScore"), max);
		};
	}

	public static Specification<User> hasFinishedProjects(Set<String> finishedProjects) {
		return (table, query, criteria) -> {
			if (finishedProjects == null || finishedProjects.isEmpty()) {
				return null;
			}
			Join<User, String> joinTable = table.joinSet("finishedProjects", JoinType.INNER);
			// find all row that has String in finishedProjects as value
			Predicate inPredicate = joinTable.in(finishedProjects);
			// group all those rows by id, essentially merge them under the same key
			query.groupBy(table.get("id"));
			// group filter to get rows that have the same number of value as size of finishedProjects
			query.having(criteria.equal(criteria.countDistinct(joinTable), finishedProjects.size()));
			return inPredicate;
		};
	}

	public static Specification<User> hasLfg(String lfg) {
		return (table, query, criteria) ->
				lfg == null ? null : criteria.equal(table.get("lfg"), lfg);
	}
}