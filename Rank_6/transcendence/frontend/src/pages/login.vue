<script setup lang="ts">
  import { ref } from 'vue'
  import { useRouter } from 'vue-router'
  import { BadRequestError, UnauthenticatedError } from '@/api/errors.ts'
  import { colors } from '@/styles/Colors.ts'
  import { signin, verifyOtp } from '../api/auth'
  import { useAuthStore } from '../stores/auth'

  type LoginPayload = { username: string, password: string }

  const router = useRouter()
  const authStore = useAuthStore()

  const isLoading = ref(false)
  const errorMessage = ref('')

  const showOtp = ref(false)
  const pendingEmail = ref('')
  const emailInput = ref('')
  const otpInput = ref('')
  const otpError = ref('')
  const isRedirecting = ref(false)
  const isConfirmHovered = ref(false)
  const isCancelHovered = ref(false)

  async function onLogin (payload: LoginPayload) {
    errorMessage.value = ''
    if (!payload.username.trim()) {
      errorMessage.value = 'Username is required.'
      return
    }
    if (!payload.password) {
      errorMessage.value = 'Password is required.'
      return
    }
    isLoading.value = true
    try {
      const result = await signin(payload.username, payload.password)
      if (result.twoFa) {
        pendingEmail.value = result.email
        emailInput.value = result.email
        otpInput.value = ''
        otpError.value = ''
        showOtp.value = true
      } else {
        const token = authStore.accessToken
        if (!token) {
          errorMessage.value = 'Authentication failed: no token received.'
          return
        }
        authStore.setSession(result.user, token)
        router.push('/home')
      }
    } catch (error) {
      if (error instanceof Error) errorMessage.value = error.message
    } finally {
      isLoading.value = false
    }
  }

  function onLogin42 () {
    window.location.href = `${import.meta.env.VITE_API_URL}/api/auth/oauth2/authorization/42`
  }

  async function onVerifyOtp () {
    const email = pendingEmail.value || emailInput.value
    const otp = Number.parseInt(otpInput.value)

    if (!email || Number.isNaN(otp) || otpInput.value.length !== 6) {
      otpError.value = 'Please enter a valid 6-digit code.'
      return
    }

    isLoading.value = true
    otpError.value = ''
    try {
      const user = await verifyOtp(email, otp)
      const token = authStore.accessToken
      if (!token) {
        otpError.value = 'Authentication failed: no token received.'
        return
      }
      authStore.setSession(user, token)
      router.push('/home')
    } catch (error) {
      if (error instanceof UnauthenticatedError) {
        otpError.value = 'Wrong email or Max attempt reached. Redirecting to login page after 3 seconds...'
        isRedirecting.value = true
        setTimeout(() => window.location.href = '/login', 3000)
      } else if (error instanceof BadRequestError) {
        otpError.value = 'Invalid or expired OTP.'
      } else if (error instanceof Error) {
        otpError.value = error.message
      }
    } finally {
      isLoading.value = false
    }
  }
</script>

<template>
  <div>
    <LoginSections
      :error-message="errorMessage"
      :is-loading="isLoading"
      @login="onLogin"
      @login42="onLogin42"
    />

    <div v-if="showOtp">
      <div
        class="fixed inset-0 z-40 opacity-70"
        :style="{ backgroundColor: colors.suite42Black }"
      />
      <div class="fixed inset-0 z-50 flex items-center justify-center">
        <div
          class="rounded p-8 w-full max-w-md flex flex-col gap-4"
          :style="{ backgroundColor: colors.suite42Background }"
        >
          <h3
            class="leading-10 font-bold font-h3-mobile
                         md:font-h3-tablet
                         lg:font-h3-laptop
                         xl:font-h3-desktop"
            :style="{ color: colors.suite42Black }"
          >
            Two-Factor Authentication
          </h3>
          <p
            class="mb-8 font-regular font-body2-mobile
                         md:font-body2-tablet
                         lg:font-body2-laptop
                         xl:font-body2-desktop"
            :style="{ color: colors.suite42Darkgrey }"
          >
            A 6-digit code has been sent to your email.
          </p>
          <div class="flex flex-col gap-8">
            <InputField
              v-if="!pendingEmail"
              v-model="emailInput"
              label="Email"
              placeholder="your@email.com"
              type="email"
            />
            <InputField
              v-model="otpInput"
              inputmode="numeric"
              label="Code"
              maxlength="6"
              placeholder="123456"
              type="text"
              @keyup.enter="onVerifyOtp"
            />
            <div class="flex flex-col gap-4">
              <p
                v-if="otpError"
                class="font-regular font-body2-mobile
                 md:font-body2-tablet
                 lg:font-body2-laptop
                 xl:font-body2-desktop"
                :style="{ color: colors.suite42Red}"
              >{{ otpError }}</p>
              <div class="flex gap-2">
                <button
                  class="flex-1 py-3 border-1 rounded cursor-pointer disabled:opacity-60 disabled:cursor-not-allowed font-semibold font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
                  :disabled="isLoading || isRedirecting"
                  :style="{
                    backgroundColor: isConfirmHovered? colors.suite42Background : colors.suite42Blue,
                    color: colors.suite42Black,
                    borderColor: colors.suite42Blue
                  }"
                  @click="onVerifyOtp"
                  @mouseleave="isConfirmHovered = false"
                  @mouseover="isConfirmHovered = true"
                >
                  {{ isLoading ? 'Verifying...' : 'Confirm' }}
                </button>
                <button
                  class="px-5 py-3 border-1 rounded cursor-pointer font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
                  :style="{
                    backgroundColor: isCancelHovered ? colors.suite42Red : colors.suite42Background,
                    color: isCancelHovered ? colors.suite42White : colors.suite42Black,
                    borderColor: isCancelHovered? colors.suite42Red : colors.suite42Background
                  }"
                  @click="showOtp = false"
                  @mouseleave="isCancelHovered = false"
                  @mouseover="isCancelHovered = true"
                >
                  Cancel
                </button>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
