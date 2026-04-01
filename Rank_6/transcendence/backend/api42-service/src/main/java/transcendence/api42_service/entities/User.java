package transcendence.api42_service.entities;

import jakarta.persistence.*;
import lombok.*;

import java.time.OffsetDateTime;
import java.util.List;
import java.util.Set;

@Getter
@Setter
@NoArgsConstructor
@Entity
@Table(name="STUDENT")
public class User {
    @Id
    private Long id;

    @ManyToOne(fetch = FetchType.EAGER, optional = false)
    @JoinColumn(name="campus_user", nullable = false)
    private Campus campus;

    @OneToMany(
            mappedBy = "user",
            fetch = FetchType.LAZY,
            cascade = {CascadeType.PERSIST, CascadeType.MERGE})
    private List<ProjectsUsers> projectsUsers;

    @Column(name="email")
    private String email;

    @Column(name="login", nullable = false)
    private String login;

    @Column(name="first_name")
    private String firstName;

    @Column(name="last_name")
    private String lastName;

    @Column(name="url")
    private String intraUrl;

    @Column(name="custom_avatar_url")
    private String customAvatarUrl;

    @Column(name="custom_banner_url")
    private String customBannerUrl;

    @Column(name="image_link")
    private String imageLink;

    @Column(name="image_large")
    private String imageLarge;

    @Column(name="image_medium")
    private String imageMedium;

    @Column(name="image_small")
    private String imageSmall;

    @Column(name="image_micro")
    private String imageMicro;

    @Column(name="pool_month")
    private String poolMonth;

    @Column(name="pool_year")
    private String poolYear;

    @Column(name="created_at")
    private OffsetDateTime createdAt;

    @Column(name="updated_at")
    private OffsetDateTime updatedAt;

    @Column(name="alumni")
    private Boolean alumni;

    @Column(name="active")
    private Boolean active;

    @Column(name="current_rank")
    private Integer rank;

    @Column(name = "freeze_days")
    private Integer freezeDays;

    @Column(name="rank_progress_percent")
    private Integer rankProgressPercent;

    @Column(name = "performance_score")
    private Integer performanceScore;

    @Column(name="lfg")
    @NonNull
    private String lfg = "none";

    @ElementCollection(fetch=FetchType.EAGER)
    @CollectionTable(
            name="user_finished_projects",
            joinColumns = @JoinColumn(name="user_id"))
    @Column(name="project")
    private Set<String> finishedProjects;

    @ElementCollection(fetch=FetchType.EAGER)
    @CollectionTable(
            name="user_eligible_projects",
            joinColumns = @JoinColumn(name="user_id"))
    @Column(name="project")
    private Set<String> eligibleProjects;

    @Column(name="last_seen")
    private OffsetDateTime lastSeen;

    @Column(columnDefinition="TEXT")
    private String detailedProfileJson;

    @OneToOne(cascade = {CascadeType.PERSIST, CascadeType.MERGE})
    @JoinColumn(name = "pool_result_id")
    private PoolResult poolResult;

}