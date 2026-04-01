package transcendence.api42_service.definition.curriculum;

import java.util.Set;

public record RankDefinition(
		Set<String> mandatory,
		Set<Set<String>> choices
) {

	public boolean containsSlug(String slug) {
		if (mandatory.contains(slug)) {
			return true;
		}
		return choices.stream()
				.anyMatch(group -> group.contains(slug));
	}
}