<template>
  <SignupSections
    :error-message="errorMessage"
    :is-loading="isLoading"
    :success-message="successMessage"
    @signup="onSignup"
  />
</template>

<script setup lang="ts">
  import { ref } from 'vue'
  import { useRouter } from 'vue-router'
  import { signup } from '../api/auth'

  type SignupPayload = {
    username: string
    email: string
    password: string
    confirmPassword: string
    agreeToTerms: boolean
  }

  const isLoading = ref(false)
  const errorMessage = ref('')
  const successMessage = ref('')
  const router = useRouter()

  function isValidEmail (email: string): boolean {
    return /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)
  }

  async function onSignup (payload: SignupPayload) {
    errorMessage.value = ''

    if (!payload.username || payload.username.length < 3) {
      errorMessage.value = 'Username must be at least 3 characters'
      return
    }

    if (!isValidEmail(payload.email)) {
      errorMessage.value = 'Invalid email format'
      return
    }

    if (payload.password.length < 8) {
      errorMessage.value = 'Password must be at least 8 characters'
      return
    }

    if (!/[A-Z]/.test(payload.password)) {
      errorMessage.value = 'Password must contain at least one uppercase letter'
      return
    }

    if (!/[a-z]/.test(payload.password)) {
      errorMessage.value = 'Password must contain at least one lowercase letter'
      return
    }

    if (!/\d/.test(payload.password)) {
      errorMessage.value = 'Password must contain at least one digit'
      return
    }

    if (payload.password !== payload.confirmPassword) {
      errorMessage.value = 'Passwords do not match'
      return
    }

    if (!payload.agreeToTerms) {
      errorMessage.value = 'You must accept the Terms of Service to continue'
      return
    }

    isLoading.value = true

    try {
      await signup(payload.username, payload.email, payload.password)
      successMessage.value = 'Account created successfully! Redirecting to login...'
      setTimeout(() => router.push('/login'), 2000)
    } catch (error) {
      if (error instanceof Error) {
        errorMessage.value = error.message
      }
    } finally {
      isLoading.value = false
    }
  }
</script>
