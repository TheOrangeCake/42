package com.transcendance.chatservice.controller;

import com.transcendance.chatservice.model.ChatMessage;
import com.transcendance.chatservice.service.ChatMessageService;
import lombok.RequiredArgsConstructor;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController // On utilise RestController pour pouvoir aussi exposer des URLs classiques (historique)
@RequiredArgsConstructor
public class ChatController {

    // L'outil magique de Spring pour envoyer des messages à des utilisateurs précis
    private final SimpMessagingTemplate messagingTemplate;
    private final ChatMessageService chatMessageService;

    /**
     * Cette méthode est appelée quand un client envoie un message à "/app/chat"
     * FIX: Ajout de la validation et de la gestion d'erreur
     */
    @MessageMapping("/chat")
    public void processMessage(@Payload ChatMessage chatMessage) {
        // FIX: Validation des données
        if (chatMessage == null || chatMessage.getRecipientId() == null || 
            chatMessage.getContent() == null || chatMessage.getContent().trim().isEmpty()) {
            throw new IllegalArgumentException("Message ou destinataire invalide");
        }

        try {
            // 1. On sauvegarde le message en base de données via le service
            ChatMessage savedMsg = chatMessageService.save(chatMessage);

            // 2. On l'envoie au destinataire (recipientId)
            // Spring va transformer "/user/queue/messages" en une file privée
            // propre à l'utilisateur ciblé.
            messagingTemplate.convertAndSendToUser(
                    chatMessage.getRecipientId(),
                    "/queue/messages",
                    savedMsg
            );
        } catch (Exception e) {
            throw new RuntimeException("Erreur lors de l'envoi du message: " + e.getMessage(), e);
        }
    }

    /**
     * Route HTTP classique pour récupérer l'historique entre deux utilisateurs
     */
    @GetMapping("/messages/{senderId}/{recipientId}")
    public List<ChatMessage> findChatMessages(@PathVariable String senderId,
                                              @PathVariable String recipientId) {
        return chatMessageService.findChatMessages(senderId, recipientId);
    }
}