package transcendence.api42_service.entities;

import jakarta.persistence.*;
import lombok.*;

import java.util.List;

@Getter
@Setter
@NoArgsConstructor
@Entity
@Table(name="CAMPUS")
public class Campus {
	@Id
	private Long id;

	@OneToMany(
			mappedBy = "campus",
			fetch = FetchType.LAZY,
			cascade = {CascadeType.PERSIST, CascadeType.MERGE})
	private List<User> users;

	@Column(name="name", unique = true, nullable = false)
	private String name;

	@Column(name="time_zone")
	private String timeZone;

	@Column(name="users_count")
	private Long usersCount;

	@Column(name="country")
	private String country;

	@Column(name="address")
	private String address;

	@Column(name="zip")
	private String zip;

	@Column(name="city")
	private String city;

	@Column(name="website")
	private String website;

	@Column(name="facebook")
	private String facebook;

	@Column(name="twitter")
	private String twitter;

	@Column(name="active")
	private Boolean active;

	@Column(name="public")
	private Boolean publicCampus;

	@Column(name="email_extension")
	private String emailExtension;

}