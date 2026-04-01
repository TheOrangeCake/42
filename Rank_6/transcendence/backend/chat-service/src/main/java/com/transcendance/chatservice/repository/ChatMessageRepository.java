package com.transcendance.chatservice.repository;

import com.transcendance.chatservice.model.ChatMessage;
import org.springframework.data.jpa.repository.JpaRepository;
import java.util.List;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

public interface ChatMessageRepository extends JpaRepository<ChatMessage, Long> {

    // FIX: Méthode simple - conversation d'une direction
    List<ChatMessage> findBySenderIdAndRecipientId(String senderId, String recipientId);

    // FIX: Requête JPQL pour récupérer l'historique complet (dans les deux sens)
    // et trier par timestamp croissant
    @Query("SELECT m FROM ChatMessage m WHERE " +
           "(m.senderId = :senderId AND m.recipientId = :recipientId) OR " +
           "(m.senderId = :recipientId AND m.recipientId = :senderId) " +
           "ORDER BY m.timestamp ASC")
    List<ChatMessage> findConversation(@Param("senderId") String senderId, 
                                       @Param("recipientId") String recipientId);
}