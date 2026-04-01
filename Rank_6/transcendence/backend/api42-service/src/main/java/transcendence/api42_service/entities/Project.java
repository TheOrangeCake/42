package transcendence.api42_service.entities;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.List;

@Getter
@Setter
@NoArgsConstructor
@Entity
@Table(name="PROJECT")
public class Project {
	@Id
	private Long id;

	@Column(name="name")
	private String name;

	@Column(name="slug")
	private String slug;

	@Column(name="rank")
	private Integer rank;

	@OneToMany(
			mappedBy = "project",
			fetch = FetchType.LAZY,
			cascade = {CascadeType.PERSIST, CascadeType.MERGE})
	private List<ProjectsUsers> projectsUsers;
}