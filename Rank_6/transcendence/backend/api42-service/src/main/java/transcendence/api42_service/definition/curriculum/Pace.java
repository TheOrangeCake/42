package transcendence.api42_service.definition.curriculum;

public enum Pace {
    RANK_0(30, 30),
    RANK_1(90, 60),
    RANK_2(180, 90),
    RANK_3(300, 120),
    RANK_4(420, 120),
    RANK_5(570, 150),
    RANK_6(720, 150);

    private final long daysToFinishRankAccumulation;
    private final long daysToFinishRank;

    Pace(int daysToFinishRankAccumulation, int daysToFinishRank) {
        this.daysToFinishRankAccumulation = daysToFinishRankAccumulation;
        this.daysToFinishRank = daysToFinishRank;
    }

    public static long getDaysToFinishRank(int userRank) {
        return switch (userRank) {
            case (0) -> RANK_0.daysToFinishRank;
            case (1) -> RANK_1.daysToFinishRank;
            case (2) -> RANK_2.daysToFinishRank;
            case (3) -> RANK_3.daysToFinishRank;
            case (4) -> RANK_4.daysToFinishRank;
            case (5) -> RANK_5.daysToFinishRank;
            default -> RANK_6.daysToFinishRank;
        };
    }

    public static long getDaysToFinishRankAccumulation(int userRank) {
        return switch (userRank) {
            case (0) -> RANK_0.daysToFinishRankAccumulation;
            case (1) -> RANK_1.daysToFinishRankAccumulation;
            case (2) -> RANK_2.daysToFinishRankAccumulation;
            case (3) -> RANK_3.daysToFinishRankAccumulation;
            case (4) -> RANK_4.daysToFinishRankAccumulation;
            case (5) -> RANK_5.daysToFinishRankAccumulation;
            default -> RANK_6.daysToFinishRankAccumulation;
        };
    }
}