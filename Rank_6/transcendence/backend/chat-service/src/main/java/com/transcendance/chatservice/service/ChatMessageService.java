package com.transcendance.chatservice.service;

import java.util.Date;
import java.util.List;

import org.springframework.stereotype.Service;
import lombok.RequiredArgsConstructor;

import com.transcendance.chatservice.model.ChatMessage;
import com.transcendance.chatservice.model.MessageStatus;
import com.transcendance.chatservice.repository.ChatMessageRepository;

@Service
@RequiredArgsConstructor
public class ChatMessageService {

    private final ChatMessageRepository repository;
    private final FriendshipClient friendshipClient;

    public ChatMessage save(ChatMessage message) {
        if (message.getContent() == null || message.getContent().trim().isEmpty()) {
            throw new IllegalArgumentException("Le contenu du message ne peut pas être vide");
        }

        if (message.getSenderId() == null || message.getRecipientId() == null) {
            throw new IllegalArgumentException("senderId et recipientId sont obligatoires");
        }

        if (!friendshipClient.areFriends(message.getSenderId(), message.getRecipientId())) {
            throw new IllegalArgumentException("You must be friends to send messages");
        }

        message.setTimestamp(new Date());
        if (message.getStatus() == null) {
            message.setStatus(MessageStatus.RECEIVED);
        }

        return repository.save(message);
    }

    public List<ChatMessage> findChatMessages(String senderId, String recipientId) {
        return repository.findConversation(senderId, recipientId);
    }
}
