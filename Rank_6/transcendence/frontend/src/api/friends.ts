import { http } from './http'

const BASE = '/api/api42/v1/42users/friends'

export interface FriendshipDto {
  id: number
  friend_id: number
  friend_login: string
  friend_avatar_url: string
  status: string
  is_requester: boolean
  online: boolean
}

export function getFriends () {
  return http.get<FriendshipDto[]>(BASE)
}

export function getPendingRequests () {
  return http.get<FriendshipDto[]>(`${BASE}/pending`)
}

export function getSentRequests () {
  return http.get<FriendshipDto[]>(`${BASE}/sent`)
}

export function sendFriendRequest (userId: number) {
  return http.post<FriendshipDto>(`${BASE}/${userId}`)
}

export function acceptFriendRequest (friendshipId: number) {
  return http.put<FriendshipDto>(`${BASE}/${friendshipId}/accept`)
}

export function declineFriendRequest (friendshipId: number) {
  return http.put<FriendshipDto>(`${BASE}/${friendshipId}/decline`)
}

export function removeFriend (friendshipId: number) {
  return http.delete<void>(`${BASE}/${friendshipId}`)
}

export function checkFriendship (userId: number) {
  return http.get<{ friends: boolean }>(`${BASE}/check/${userId}`)
}

export interface UserSearchResult {
  id: number
  login: string
  avatar_url: string
}

export function searchUsers (login: string) {
  return http.get<UserSearchResult[]>(`${BASE}/search`, { login })
}

export function sendHeartbeat () {
  return http.post<void>(`${BASE}/heartbeat`)
}
