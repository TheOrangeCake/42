package com.example.regular_user_service.entities;

import jakarta.persistence.*;
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Pattern;
import lombok.*;

import java.util.Date;

@Getter
@Setter
@NoArgsConstructor
@Entity
@Table(name="REGULAR_USER")
public class User {

	@Id
	@GeneratedValue
	private Long id;

	@NotBlank(message="Username can not be blank")
	@Pattern(
			regexp = "^[A-Za-z0-9_]+( [A-Za-z0-9_]+)*$",
			message = "Username may only contain letters, numbers, spaces, and underscores. No leading or trailing whitespaces."
	)
	@Column(name = "username", unique = true, nullable = false)
	private String username;

	@NotBlank(message="Email can not be blank")
	@Email(regexp = ".+@.+\\..+")
	@Column(name = "email", unique = true, nullable = false)
	private String email;

	@NotBlank(message="Password can not be blank")
	@Column(name = "password")
	private String password;

	@Column(name = "custom_avatar_url")
	private String customAvatarUrl;

	@Column(name = "custom_banner_url")
	private String customBannerUrl;

	@Column(name = "first_name")
	private String firstName;

	@Column(name = "last_name")
	private String lastName;

	@Column(name = "login_attempt")
	private int loginAttempt = 0;

	@Column(name = "double_auth")
	private boolean doubleAuth = false;

	@Column(name = "created_at")
	private Date createdAt;

	@Column(name = "active")
	private boolean active;
}