import { http } from './http'
import { UnauthenticatedError, ServerError } from './errors'
import { useAuthStore } from '../stores/auth'

export interface User {
  id: number
  username: string
  email: string
  custom_avatar_url: string
  custom_banner_url: string
  first_name: string | null
  last_name: string | null
  double_authentication: boolean
}

export type SigninResult =
  | { twoFa: false; user: User }
  | { twoFa: true; email: string }

const BASE = '/api/regular-user/v1/regular-user'
const API_BASE_URL = import.meta.env.VITE_API_URL

export function signup(username: string, email: string, password: string) {
  return http.post<User>(`${BASE}/auth/signup`, { username, email, password })
}

export async function signin(login: string, password: string): Promise<SigninResult> {
  const authStore = useAuthStore()

  const response = await fetch(`${API_BASE_URL}${BASE}/auth/signin`, {
    method: 'POST',
    credentials: 'include',
    headers: {
      'Content-Type': 'application/json',
      ...(authStore.accessToken && { 'Authorization': `Bearer ${authStore.accessToken}` }),
    },
    body: JSON.stringify({ login, password }),
  })

  if (response.status === 202) {
    return { twoFa: true, email: login.includes('@') ? login : '' }
  }

  if (response.ok) {
    const token = response.headers.get('Authorization')?.replace('Bearer ', '')
    if (token) authStore.accessToken = token
    const user: User = await response.json()
    return { twoFa: false, user }
  }

  const errorData = await response.json().catch(() => ({}))
  const message = errorData.message || errorData.error || 'Unknown error'
  if (response.status === 401) throw new UnauthenticatedError(message)
  throw new ServerError(message)
}

export function verifyOtp(email: string, otp: number) {
  return http.post<User>(`${BASE}/auth/verify-otp`, { email, otp })
}

export interface Me42Response {
  authenticated: boolean
  sub: string
  token?: string
}

export function getMe42() {
  return http.get<Me42Response>('/api/auth/me')
}

export function logout42() {
  return http.post<void>('/api/auth/logout')
}

export function refreshToken() {
  return http.get<User>(`${BASE}/auth/refresh-token`)
}

export function signout() {
  return http.get<void>(`${BASE}/user/signout`)
}

export function getMyProfile() {
  return http.get<User>(`${BASE}/user/profile`)
}

export interface UpdateProfileDto {
  email: string
  first_name?: string | null
  last_name?: string | null
  double_authentication: boolean
  confirm_password: string
}

export function updateMyProfile(data: UpdateProfileDto) {
  return http.put<User>(`${BASE}/user/profile`, data)
}
