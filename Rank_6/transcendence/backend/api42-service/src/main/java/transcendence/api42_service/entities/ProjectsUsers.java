package transcendence.api42_service.entities;

import jakarta.persistence.*;
import lombok.*;

import java.time.OffsetDateTime;

@Getter
@Setter
@NoArgsConstructor
@Entity
@Table(name="PROJECTS_USER")
public class ProjectsUsers {
	@Id
	private Long id;

	@Column(name="occurrence")
	private Integer occurrence;

	@Column(name="final_mark")
	private Integer finalMark;

	@Column(name="status")
	private String status;

	@Column(name="validated")
	private Boolean validated;

	@Column(name="marked_at")
	private OffsetDateTime markedAt;

	@ManyToOne(fetch=FetchType.LAZY, optional = false)
	@JoinColumn(name="user_projects_users", nullable = false)
	private User user;

	@ManyToOne(fetch=FetchType.LAZY, optional = false)
	@JoinColumn(name="project_projects_users", nullable = false)
	private Project project;
}