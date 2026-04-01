export class ApiError extends Error {
  constructor (message?: string) {
    super(message)
  }
}
export class UnauthenticatedError extends Error {
  constructor (message = 'Unauthenticated') {
    super(message)
    this.name = 'UnauthenticatedError'
  }
}

export class ForbiddenError extends Error {
  constructor (message = 'Forbidden') {
    super(message)
    this.name = 'ForbiddenError'
  }
}

export class NotFoundError extends Error {
  constructor (message = 'Not found') {
    super(message)
    this.name = 'NotFoundError'
  }
}

export class ValidationError extends Error {
  data: unknown
  constructor (data: unknown) {
    super('Validation error')
    this.name = 'ValidationError'
    this.data = data
  }
}

export class ServerError extends Error {
  constructor (message = 'Server error') {
    super(message)
    this.name = 'ServerError'
  }
}

export class ConflictError extends Error {
  constructor (message = 'Conflict') {
    super(message)
    this.name = 'ConflictError'
  }
}

export class BadRequestError extends Error {
  constructor (message = 'Bad Request') {
    super(message)
    this.name = 'BadRequestError'
  }
}
