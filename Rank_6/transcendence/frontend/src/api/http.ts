import { useAuthStore } from '../stores/auth'
import {
  BadRequestError,
  ConflictError,
  ForbiddenError,
  NotFoundError,
  ServerError,
  UnauthenticatedError, ValidationError,
} from './errors'

const API_BASE_URL = import.meta.env.VITE_API_URL

async function request<T> (url: string, options: RequestInit = {}): Promise<T> {
  const authStore = useAuthStore()

  const response = await fetch(`${API_BASE_URL}${url}`, {
    credentials: 'include',
    headers: {
      'Content-Type': 'application/json',
      ...(authStore.accessToken && {
        Authorization: `Bearer ${authStore.accessToken}`,
      }),
      ...options.headers,
    },
    ...options,
  })

  if (response.ok) {
    const token = response.headers.get('Authorization')?.replace('Bearer ', '')
    if (token) {
      authStore.accessToken = token
    }

    if (response.status === 204) {
      return null as T
    }
    return response.json()
  }

  const errorData = await response.json().catch(() => ({}))
  const message = typeof errorData === 'string'
    ? errorData
    : (errorData.message || errorData.error || 'Unknown error')

  if (response.status === 400) {
    throw new BadRequestError(message)
  }
  if (response.status === 401) {
    throw new UnauthenticatedError(message)
  }
  if (response.status === 403) {
    throw new ForbiddenError(message)
  }
  if (response.status === 404) {
    throw new NotFoundError(message)
  }
  if (response.status === 409) {
    throw new ConflictError(message)
  }
  if (response.status === 422) {
    throw new ValidationError(errorData)
  }
  throw new ServerError(message)
}

export const http = {
  get<T>(url: string, params?: Record<string, string> | URLSearchParams) {
    const query = params ? `?${new URLSearchParams(params)}` : ''
    return request<T>(`${url}${query}`)
  },
  post<T>(url: string, body?: unknown) {
    return request<T>(url, { method: 'POST', body: JSON.stringify(body) })
  },
  put<T>(url: string, body?: unknown) {
    return request<T>(url, { method: 'PUT', body: JSON.stringify(body) })
  },
  delete<T>(url: string) {
    return request<T>(url, { method: 'DELETE' })
  },
  patch<T>(url: string, body?: unknown) {
    return request<T>(url, { method: 'PATCH', body: body === undefined ? undefined : JSON.stringify(body) })
  },
}
