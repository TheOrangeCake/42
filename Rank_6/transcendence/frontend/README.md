# Frontend - Transcendence

This frontend is a Vue 3 single page application using Vuetify, Pinia and Vue Router.

The project uses session-based authentication with HttpOnly cookies.
The frontend never reads or stores the session token directly.
Authentication state is retrieved from the backend using a dedicated endpoint.

## Architecture overview

The frontend is organized around clear responsibilities:

- API layer: handles all HTTP requests and error normalization
- Stores (Pinia): handle application state and business logic
- Router: protects private routes
- Pages and components: handle UI only

## API layer

The api layer centralizes all fetch calls and HTTP configuration.
It is responsible for:
- sending cookies with requests
- handling JSON requests and responses
- converting HTTP status codes into frontend errors

## Authentication flow

- Login sends credentials to the backend
- Backend sets a HttpOnly session cookie
- Frontend calls /me to retrieve the current user
- Auth state is stored in a Pinia store
- Protected routes require authentication

## Route protection

Private pages define a requiresAuth meta field.
The router checks authentication state before navigation and redirects to /login if needed.

## Current state

This is a base foundation for the frontend.
UI integration (login form, error handling, loaders) will be added next.

