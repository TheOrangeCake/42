import { http } from './http'

export interface IndividualProject {
  cursus_project_id: number
  name: string
  slug: string
  projects_users: {
    occurrence: number
    final_mark: number | null
    status: string
    validated: boolean | null
  } | null
}

export interface IndividualRank {
  rank: number
  projects: IndividualProject[]
}

export interface UserDetailed {
  id: number
  campus: string
  email: string
  login: string
  first_name: string
  last_name: string
  intra_url: string
  custom_avatar_url: string | null
  custom_banner_url: string | null
  image: {
    link: string | null
    versions: {
      large: string | null
      medium: string | null
      small: string | null
      micro: string | null
    }
  }
  pool_month: string | null
  pool_year: string | null
  alumni: boolean
  active: boolean
  rank: number
  rank_progress_percent: number
  performance_score: number
  finished_projects: string[]
  eligible_projects: string[]
  common_core: {
    rank: IndividualRank[]
  }
}

export interface User42 {
  id: number
  login: string
  first_name: string
  last_name: string
  intra_url: string
  custom_avatar_url: string | null
  image: {
    versions: {
      small: string | null
      medium: string | null
    }
  }
  pool_month: string | null
  pool_year: string | null
  rank: number
  rank_progress_percent: number
  performance_score: number
}

export interface PagedResponse<T> {
  content: T[]
  page: {
    size: number
    number: number
    totalElements: number
    totalPages: number
  }
}

export interface FinderFilters {
  campusName: string
  page: number
  size: string
  rank?: string
  poolYear?: string
  poolMonth?: string
  eligibleProject?: string
  finishedProjects?: string[]
  minScore?: number
  maxScore?: number
  sort?: string
  search?: string
}

export function getUsers (filters: FinderFilters) {
  const params = new URLSearchParams()
  params.set('campusName', filters.campusName)
  params.set('page', filters.page.toString())
  params.set('size', filters.size)

  if (filters.rank && filters.rank !== 'all') {
    params.set('rank', filters.rank)
  }
  if (filters.poolYear && filters.poolYear !== 'all') {
    params.set('poolYear', filters.poolYear)
  }
  if (filters.poolMonth && filters.poolMonth !== 'all') {
    params.set('poolMonth', filters.poolMonth)
  }
  if (filters.eligibleProject && filters.eligibleProject !== 'any') {
    params.set('eligibleProject', filters.eligibleProject)
  }
  if (filters.finishedProjects) {
    for (const p of filters.finishedProjects) {
      params.append('finishedProjects', p)
    }
  }
  if (filters.minScore !== undefined && filters.minScore !== null) {
    params.set('minScore', filters.minScore.toString())
  }
  if (filters.maxScore !== undefined && filters.maxScore !== null) {
    params.set('maxScore', filters.maxScore.toString())
  }
  if (filters.sort) {
    params.set('sort', filters.sort)
  }
  if (filters.search) {
    params.set('search', filters.search)
  }
  return http.get<PagedResponse<User42>>('/api/api42/v1/42users', params)
}

export function getUserProfile () {
  return http.get<UserDetailed>('/api/api42/v1/42users/profile')
}

export function getUserByLogin (login: string) {
  return http.get<UserDetailed>(`/api/api42/v1/42users/profile/login/${login}`)
}
