package com.example.regular_user_service.entities;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.util.Date;

@Entity
@Getter
@Setter
@Table(name="REVOKED_TOKEN")
public class RevokedToken {

    @Id
    private String token;

    @Column(name = "token_type")
    private String type;

    @Column(name = "revoked_at")
    private Date revokedAt;
}
