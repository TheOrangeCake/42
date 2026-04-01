package transcendence.api42_service.entities;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.Date;

@Getter
@Setter
@NoArgsConstructor
@Entity
@Table(name = "FRIENDSHIP", uniqueConstraints = {
	@UniqueConstraint(columnNames = {"requester_id", "addressee_id"})
})
public class Friendship {

	@Id
	@GeneratedValue
	private Long id;

	@ManyToOne(optional = false)
	@JoinColumn(name = "requester_id", nullable = false)
	private User requester;

	@ManyToOne(optional = false)
	@JoinColumn(name = "addressee_id", nullable = false)
	private User addressee;

	@Enumerated(EnumType.STRING)
	@Column(name = "status", nullable = false)
	private FriendshipStatus status = FriendshipStatus.PENDING;

	@Column(name = "created_at")
	private Date createdAt;

	@PrePersist
	protected void onCreate() {
		this.createdAt = new Date();
	}
}
