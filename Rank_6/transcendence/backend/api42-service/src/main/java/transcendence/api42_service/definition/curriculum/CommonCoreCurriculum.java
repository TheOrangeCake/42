package transcendence.api42_service.definition.curriculum;

import java.util.Map;
import java.util.Set;
import java.util.SortedMap;
import java.util.TreeMap;

// Hard code? Yes
@SuppressWarnings("SpellCheckingInspection")
public final class CommonCoreCurriculum {
	public static final SortedMap<Integer, RankDefinition> RANKS = new TreeMap<>();

	static {
		RANKS.put(0, new RankDefinition(
				Set.of("42cursus-libft"),
				Set.of()
		));
		RANKS.put(1, new RankDefinition(
				Set.of(
						"42cursus-get_next_line",
						"42cursus-ft_printf",
						"born2beroot"
				),
				Set.of()
		));
		RANKS.put(2, new RankDefinition(
				Set.of(
						"42cursus-push_swap",
						"exam-rank-02"
				),
				Set.of(
						Set.of(
								"42cursus-fdf",
								"42cursus-fract-ol",
								"so_long"
						),
						Set.of(
								"pipex",
								"minitalk"
						)
				)
		));
		RANKS.put(3, new RankDefinition(
				Set.of(
						"42cursus-minishell",
						"42cursus-philosophers",
						"exam-rank-03"
				),
				Set.of()
		));
		RANKS.put(4, new RankDefinition(
				Set.of(
						"netpractice",
						"cpp-module-00",
						"cpp-module-01",
						"cpp-module-02",
						"cpp-module-03",
						"cpp-module-04",
						"exam-rank-04"
				),
				Set.of(
						Set.of(
								"minirt",
								"cub3d"
						)
				)
		));
		RANKS.put(5, new RankDefinition(
				Set.of(
						"inception",
						"cpp-module-05",
						"cpp-module-06",
						"cpp-module-07",
						"cpp-module-08",
						"cpp-module-09",
						"exam-rank-05"
				),
				Set.of(
						Set.of(
								"webserv",
								"ft_irc"
						)
				)
		));
		RANKS.put(6, new RankDefinition(
				Set.of(
						"ft_transcendence",
						"42_collaborative_resume",
						"exam-rank-06"
				),
				Set.of()
		));
	}

	public static Integer getProjectRank(String projectSlug) {
		return RANKS.entrySet()
				.stream()
				.filter(entry -> entry.getValue().containsSlug(projectSlug))
				.map(Map.Entry::getKey)
				.findFirst()
				.orElse(null);
	}

	public static RankDefinition getRank(int rank) {
		return RANKS.get(rank);
	}
}