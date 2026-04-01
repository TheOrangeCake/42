package com.transcendance.chatservice.model;

/**
 * Énumération pour tracker l'état d'un message
 */
public enum MessageStatus {
    SENT,        // Message envoyé mais pas encore reçu
    RECEIVED,    // Message reçu par le serveur
    DELIVERED,   // Message reçu par le client
    READ         // Message lu par le destinataire
}
