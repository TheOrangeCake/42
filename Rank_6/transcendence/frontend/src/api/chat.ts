import { Client, type IMessage, StompHeaders } from '@stomp/stompjs'
import SockJS from 'sockjs-client'
import { http } from './http'
import { useAuthStore } from '../stores/auth'

export interface ChatMessage {
  senderId: string
  recipientId: string
  content: string
  timestamp: number
}

let stompClient: Client | null = null

const WS_URL = import.meta.env.VITE_CHAT_URL

export function connectChat(
  userId: string,
  onMessage: (msg: ChatMessage) => void,
  onConnectionChange?: (connected: boolean) => void
) {
  const authStore = useAuthStore()

  if (stompClient && stompClient.connected) {
    return
  }

  console.log(`Connecting to chat WebSocket at ${WS_URL}/ws-chat`)

  stompClient = new Client({
    // SockJS retourne un objet WebSocket-like
    // @ts-ignore
    webSocketFactory: () => new SockJS(`${WS_URL}/ws-chat`),

    connectHeaders: authStore.accessToken
      ? { Authorization: `Bearer ${authStore.accessToken}` } as StompHeaders
      : {},

    reconnectDelay: 5000, // reconnect automatique

    debug: (msg: string) => console.log('STOMP:', msg),

    onConnect: () => {
      console.log('Chat WebSocket connected')
      onConnectionChange?.(true)

      stompClient?.subscribe(
        `/user/queue/messages`,
        (frame: IMessage) => {
          console.log('[WS] MESSAGE RECEIVED — raw body:', frame.body)
          try {
            const message: ChatMessage = JSON.parse(frame.body)
            console.log('[WS] Parsed message:', message)
            onMessage(message)
          } catch (err) {
            console.error('[WS] Failed to parse message:', err)
          }
        }
      )
    },

    onDisconnect: () => {
      onConnectionChange?.(false)
    },

    onStompError: (frame) => {
      console.error('Broker error:', frame.headers['message'])
      console.error('Details:', frame.body)
      onConnectionChange?.(false)
    },

    onWebSocketError: (event: Event) => {
      console.error('WebSocket error:', event)
      onConnectionChange?.(false)
    },
  })

  stompClient.activate()
}

export function sendMessage(msg: ChatMessage) {
  if (!stompClient || !stompClient.connected) {
    console.warn('STOMP client not connected')
    return
  }

  stompClient.publish({
    destination: '/app/chat',
    body: JSON.stringify(msg),
  })
}

export function disconnectChat() {
  if (stompClient) {
    stompClient.deactivate()
    stompClient = null
    console.log('Chat WebSocket disconnected')
  }
}

export function getMessageHistory(senderId: string, recipientId: string) {
  return http.get<ChatMessage[]>(
    `/api/chat/messages/${senderId}/${recipientId}`
  )
}