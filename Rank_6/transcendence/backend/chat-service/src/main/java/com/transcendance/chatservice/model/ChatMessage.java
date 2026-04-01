package com.transcendance.chatservice.model;

import jakarta.persistence.*;
import lombok.*;
import java.util.Date;

@Entity               // Dit à Spring que c'est une table en base de données
@Table(name = "messages")
@Data                 // Génère les getters, setters, toString (Lombok)
@NoArgsConstructor    // Génère un constructeur vide (obligatoire pour JPA)
@AllArgsConstructor   // Génère un constructeur avec tous les champs
@Builder              // Permet de créer l'objet plus facilement
public class ChatMessage {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false)
    private String senderId;    // Le pseudo ou l'ID de celui qui envoie

    @Column(nullable = false)
    private String recipientId; // Le pseudo ou l'ID de celui qui reçoit

    @Column(nullable = false, length = 5000)
    private String content;     // Le texte du message (max 5000 caractères)

    @Temporal(TemporalType.TIMESTAMP)
    @Column(nullable = false)
    private Date timestamp;     // L'heure d'envoi

    @Enumerated(EnumType.STRING)
    @Column(nullable = false)
    private MessageStatus status; // Reçu, Lu, etc.
}