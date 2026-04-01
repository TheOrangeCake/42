<script setup lang="ts">
  import type { UserDetailed } from '../api/api42'
  import type { User } from '../api/auth'
  import { computed, onMounted, ref } from 'vue'
  import { viewportValue } from '@/composables/viewportsValue.ts'
  import { colors } from '@/styles/Colors.ts'
  import { getUserProfile } from '../api/api42'
  import { getMyProfile, updateMyProfile } from '../api/auth'
  import { useAuthStore } from '../stores/auth'

  definePage({
    meta: {
      requiresAuth: true,
      layout: 'dashboard',
    },
  })

  const authStore = useAuthStore()
  const profile42 = ref<UserDetailed | null>(null)
  const profileRegular = ref<User | null>(null)
  const isLoading = ref(false)
  const loadError = ref('')
  const isSaving = ref(false)
  const saveError = ref('')
  const saveSuccess = ref(false)

  // 42 user fields
  const avatarFile = ref<File | null>(null)
  const bannerFile = ref<File | null>(null)
  const avatarPreview = ref<string | null>(null)
  const bannerPreview = ref<string | null>(null)

  // Regular user fields
  const regAvatarFile = ref<File | null>(null)
  const regBannerFile = ref<File | null>(null)
  const regAvatarPreview = ref<string | null>(null)
  const regBannerPreview = ref<string | null>(null)
  const twoFaEnabled = ref(false)
  const confirmPassword = ref('')

  const API_BASE_URL = import.meta.env.VITE_API_URL

  const fullName42 = computed(() => {
    if (!profile42.value) return ''
    return `${profile42.value.first_name ?? ''} ${profile42.value.last_name ?? ''}`.trim() || profile42.value.login
  })

  const avatarUrl = computed(() => {
    if (!profile42.value) return '/design/assets/images/default_avatar_cropped.jpg'
    return profile42.value.custom_avatar_url
      || profile42.value.image?.versions?.medium
      || '/design/assets/images/default_avatar_cropped.jpg'
  })

  const bannerUrl = computed(() => {
    if (!profile42.value) return '/design/assets/images/default_profile_banner.jpg'
    return profile42.value.custom_banner_url || '/design/assets/images/default_profile_banner.jpg'
  })

  function onAvatarChange (file: File | undefined) {
    if (!file) return
    if (avatarPreview.value) URL.revokeObjectURL(avatarPreview.value)
    avatarFile.value = file
    avatarPreview.value = URL.createObjectURL(file)
  }

  function onBannerChange (file: File | undefined) {
    if (!file) return
    if (bannerPreview.value) URL.revokeObjectURL(bannerPreview.value)
    bannerFile.value = file
    bannerPreview.value = URL.createObjectURL(file)
  }

  const regFullName = computed(() => {
    if (!profileRegular.value) return ''
    return `${regFirstName.value ?? ''} ${regLastName.value ?? ''}`.trim() || profileRegular.value.username
  })

  const regBannerUrl = computed(() => {
    if (!profileRegular.value) return '/design/assets/images/default_profile_banner.jpg'
    return profileRegular.value.custom_banner_url || '/design/assets/images/default_profile_banner.jpg'
  })

  const regAvatarUrl = computed(() => {
    if (!profileRegular.value) return '/design/assets/images/default_avatar_cropped.jpg'
    return profileRegular.value.custom_avatar_url || '/design/assets/images/default_avatar_cropped.jpg'
  })

  function onRegAvatarChange (file: File | undefined) {
    if (!file) return
    if (regAvatarPreview.value) URL.revokeObjectURL(regAvatarPreview.value)
    regAvatarFile.value = file
    regAvatarPreview.value = URL.createObjectURL(file)
  }

  function onRegBannerChange (file: File | undefined) {
    if (!file) return
    if (regBannerPreview.value) URL.revokeObjectURL(regBannerPreview.value)
    regBannerFile.value = file
    regBannerPreview.value = URL.createObjectURL(file)
  }

  async function uploadFile (file: File, endpoint: string, fieldName: string) {
    const formData = new FormData()
    formData.append(fieldName, file)
    const headers: Record<string, string> = {}
    if (authStore.accessToken) {
      headers['Authorization'] = `Bearer ${authStore.accessToken}`
    }
    const res = await fetch(`${API_BASE_URL}${endpoint}`, {
      method: 'PATCH',
      credentials: 'include',
      headers,
      body: formData,
    })
    if (!res.ok) {
      const data = await res.json().catch(() => ({}))
      console.error(`uploadFile failed [${res.status}] ${endpoint}:`, data)
      throw new Error(data.message || data.error || 'Upload failed')
    }
  }

  async function uploadFileRegUser (file: File, endpoint: string, fieldName: string, password: string) {
    const formData = new FormData()
    formData.append(fieldName, file)
    formData.append('confirm_password', password)
    const headers: Record<string, string> = {}
    if (authStore.accessToken) {
      headers['Authorization'] = `Bearer ${authStore.accessToken}`
    }
    const res = await fetch(`${API_BASE_URL}${endpoint}`, {
      method: 'PATCH',
      credentials: 'include',
      headers,
      body: formData,
    })
    if (!res.ok) {
      const data = await res.json().catch(() => ({}))
      console.error(`uploadFile failed [${res.status}] ${endpoint}:`, data)
      throw new Error(data.message || data.error || 'Upload failed')
    }
  }

  async function saveChanges42 () {
    saveError.value = ''
    saveSuccess.value = false
    isSaving.value = true
    try {
      if (avatarFile.value) {
        await uploadFile(avatarFile.value, '/api/api42/v1/42users/avatar', 'avatar')
      }
      if (bannerFile.value) {
        await uploadFile(bannerFile.value, '/api/api42/v1/42users/banner', 'banner')
      }
      saveSuccess.value = true
      avatarFile.value = null
      bannerFile.value = null
      if (avatarPreview.value) {
        URL.revokeObjectURL(avatarPreview.value)
        avatarPreview.value = null
      }
      if (bannerPreview.value) {
        URL.revokeObjectURL(bannerPreview.value)
        bannerPreview.value = null
      }
      profile42.value = await getUserProfile()
    } catch (error) {
      saveError.value = error instanceof Error ? error.message : 'Failed to save changes'
    } finally {
      isSaving.value = false
    }
  }

  const regLastName = ref('')
  const regFirstName = ref('')
  const regEmail = ref('')

  async function saveChangesRegular () {
    if (!profileRegular.value) return
    if (!confirmPassword.value) {
      saveError.value = 'Please confirm your password.'
      return
    }
    saveError.value = ''
    saveSuccess.value = false
    isSaving.value = true
    try {
      if (regAvatarFile.value) {
        await uploadFileRegUser(regAvatarFile.value, '/api/regular-user/v1/regular-user/user/profile/avatar', 'avatar', confirmPassword.value)
      }
      if (regBannerFile.value) {
        await uploadFileRegUser(regBannerFile.value, '/api/regular-user/v1/regular-user/user/profile/banner', 'banner', confirmPassword.value)
      }
      saveSuccess.value = true
      regAvatarFile.value = null
      regBannerFile.value = null
      if (regAvatarPreview.value) {
        URL.revokeObjectURL(regAvatarPreview.value)
        regAvatarPreview.value = null
      }
      if (regBannerPreview.value) {
        URL.revokeObjectURL(regBannerPreview.value)
        regBannerPreview.value = null
      }
      const updated = await updateMyProfile({
        email: regEmail.value || profileRegular.value.email,
        first_name: regFirstName.value || profileRegular.value.first_name,
        last_name: regLastName.value || profileRegular.value.last_name,
        double_authentication: twoFaEnabled.value,
        confirm_password: confirmPassword.value,
      })
      profileRegular.value = updated
      authStore.user = updated
      confirmPassword.value = ''
      saveSuccess.value = true
    } catch (error) {
      saveError.value = error instanceof Error ? error.message : 'Failed to save changes'
    } finally {
      isSaving.value = false
    }
  }

  onMounted(async () => {
    isLoading.value = true
    try {
      if (authStore.is42User) {
        profile42.value = await getUserProfile()
      } else {
        const user = await getMyProfile()
        profileRegular.value = user
        twoFaEnabled.value = user.double_authentication
        regEmail.value = user.email
        regFirstName.value = user.first_name || ''
        regLastName.value = user.last_name || ''
      }
    } catch (error) {
      loadError.value = error instanceof Error ? error.message : 'Failed to load profile'
    } finally {
      isLoading.value = false
    }
  })
  const uploadFieldConnector = viewportValue({
    mobile: 0.8,
    tablet: 1,
    laptop: 1,
    desktop: 1,
  })
  const connectorHeight2 = viewportValue({
    mobile: 1.2,
    tablet: 1.4,
    laptop: 1.4,
    desktop: 1.6,
  })
  const titleConnector = viewportValue({
    mobile: 1.3,
    tablet: 1.4,
    laptop: 1.5,
    desktop: 1.9,
  })
  const inputFieldConnector = viewportValue({
    mobile: 0.8,
    tablet: 1,
    laptop: 1,
    desktop: 1,
  })
</script>

<template>
  <div
    class="flex flex-col w-full px-4 mb-20 mt-28
           md:mt-12
           lg:px-8 lg:mb-48
           xl:px-18
           2xl:px-28"
  >
    <h5
      v-if="isLoading"
      class="font-regular text-center font-h5-mobile py-10
             md:font-h5-tablet
             lg:font-h5-laptop
             xl:font-h5-desktop"
      :style="{
        color: colors.suite42Black
      }"
    >Loading...</h5>
    <p
      v-else-if="loadError"
      class="font-regular text-center font-h5-mobile py-10
             md:font-h5-tablet
             lg:font-h5-laptop
             xl:font-h5-desktop"
      :style="{
        color: colors.suite42Red
      }"
    >{{ loadError }}</p>
    <div v-else-if="profile42">
      <h1
        class="font-bold font-h1-mobile
             md:font-h1-tablet
             lg:font-h1-laptop
             xl:font-h1-desktop"
        :style="{ color: colors.suite42Black }"
      >Hm, I can be a cat</h1>
      <SingleConnector color="suite42Blue" :height="3" />
      <div class="flex flex-row w-full items-start relative">
        <ConnectConnector color1="suite42Blue" color2="suite42Green" :height="4" />
        <div
          class="aspect-square w-32
                 md:w-40
                 lg:w-44
                 2xl:w-52"
        >
          <img
            alt="user avatar"
            class="object-cover w-full h-full rounded"
            :src="avatarPreview || avatarUrl"
          >
        </div>
        <div
          class="flex flex-col ml-2 gap-2 absolute top-0 bottom-0 left-42 right-0
                 md:left-54
                 lg:left-60
                 2xl:left-70"
        >
          <img alt="banner" class="object-cover rounded w-full flex-1 min-h-0" :src="bannerPreview || bannerUrl">
          <div class="flex flex-col w-fit shrink-0">
            <h2
              class="font-bold font-h4-mobile hover:underline
                     md:font-h4-tablet
                     lg:font-h4-laptop
                     xl:font-h4-desktop"
              :style="{ color: colors.suite42Black }"
            >{{ fullName42 }}</h2>
            <p
              class="font-regular font-body2-mobile
                     md:font-body2-tablet
                     lg:font-body2-laptop
                     xl:font-body2-desktop"
              :style="{ color: colors.suite42Darkgrey }"
            >{{ profile42?.email }}</p>
          </div>
        </div>
      </div>
      <SingleConnector color="suite42Green" :height="3" />
      <div class="flex flex-row">
        <ConnectConnector color1="suite42Green" color2="suite42Red" :height="uploadFieldConnector" />
        <UploadField button-text="Upload new avatar" :file="avatarFile" label="Change avatar" @change="onAvatarChange" />
      </div>
      <SingleConnector color="suite42Red" :height="2" />
      <div class="flex flex-row">
        <ConnectConnector color1="suite42Red" color2="suite42Black" :height="uploadFieldConnector" />
        <UploadField button-text="Upload new banner" :file="bannerFile" label="Change banner" @change="onBannerChange" />
      </div>
      <SingleConnector color="suite42Black" :height="4" />
      <div class="flex flex-row">
        <EndConnector color="suite42Black" :height="connectorHeight2" />
        <div class="flex flex-col gap-4 items-start">
          <div class="flex flex-row gap-12 items-center">
            <SmallRedButton :disabled="isSaving" text="Save changes" @click="saveChanges42" />
            <RouterLink
              class="font-regular font-body2-mobile hover:underline
                     md:font-body2-tablet
                     lg:font-body2-laptop
                     xl:font-body2-desktop"
              :style="{ color: colors.suite42Black }"
              to="/profile"
            >Cancel</RouterLink>
          </div>
          <div class="min-h-12">
            <p
              v-if="saveError || saveSuccess || isSaving"
              class="font-regular font-h5-mobile
                     md:font-h5-tablet
                     lg:font-h5-laptop
                     xl:font-h5-desktop"
              :style="{
                color: saveError ? colors.suite42Red : isSaving ? colors.suite42Black : colors.suite42Green
              }"
            >{{ saveError || (isSaving ? 'Uploading...' : 'Profile updated!') }}</p>
          </div>
        </div>
      </div>
    </div>
    <div v-else-if="profileRegular">
      <h1
        class="font-bold font-h1-mobile
             md:font-h1-tablet
             lg:font-h1-laptop
             xl:font-h1-desktop"
        :style="{ color: colors.suite42Black }"
      >Hm, I can be a cat</h1>
      <SingleConnector color="suite42Blue" :height="3" />
      <div class="flex flex-row w-full items-start relative">
        <ConnectConnector color1="suite42Blue" color2="suite42Green" :height="4" />
        <div
          class="aspect-square w-32
                 md:w-40
                 lg:w-44
                 2xl:w-52"
        >
          <img
            alt="user avatar"
            class="object-cover w-full h-full rounded"
            :src="regAvatarPreview || regAvatarUrl"
          >
        </div>
        <div
          class="flex flex-col ml-2 gap-2 absolute top-0 bottom-0 left-42 right-0
                 md:left-54
                 lg:left-60
                 2xl:left-70"
        >
          <img alt="banner" class="object-cover rounded w-full flex-1 min-h-0" :src="regBannerPreview || regBannerUrl">
          <div class="flex flex-col w-fit shrink-0">
            <h2
              class="font-bold font-h4-mobile
                     md:font-h4-tablet
                     lg:font-h4-laptop
                     xl:font-h4-desktop"
              :style="{ color: colors.suite42Black }"
            >{{ regFullName }}</h2>
            <p
              class="font-regular font-body2-mobile
                     md:font-body2-tablet
                     lg:font-body2-laptop
                     xl:font-body2-desktop"
              :style="{ color: colors.suite42Darkgrey }"
            >{{ regEmail }}</p>
          </div>
        </div>
      </div>
      <SingleConnector color="suite42Green" :height="3" />
      <div class="flex flex-row ">
        <ConnectConnector color1="suite42Green" color2="suite42Blue" :height="titleConnector" />
        <h3
          class="font-semibold font-h3-mobile
                 md:font-h3-tablet
                 lg:font-h3-laptop
                 xl:font-h3-desktop"
        >Personal</h3>
      </div>
      <DoubleConnectors color1="suite42Blue" color2="suite42Green" :height="1" />
      <div class="flex flex-row">
        <SingleConnectionConnector color1="suite42Blue" color2="suite42Green" color3="suite42Green" :height="inputFieldConnector" />
        <InputField v-model="regEmail" label="EMAIL" type="text" />
      </div>
      <DoubleConnectors color1="suite42Blue" color2="suite42Green" :height="2" />
      <div class="flex flex-row">
        <SingleConnectionConnector color1="suite42Blue" color2="suite42Green" color3="suite42Green" :height="inputFieldConnector" />
        <InputField v-model="regFirstName" label="FIRST NAME" type="text" />
      </div>
      <DoubleConnectors color1="suite42Blue" color2="suite42Green" :height="2" />
      <div class="flex flex-row">
        <SingleConnectionConnector color1="suite42Blue" color2="suite42Green" color3="suite42Green" :height="inputFieldConnector" />
        <InputField v-model="regLastName" label="LAST NAME" type="text" />
      </div>
      <DoubleConnectors color1="suite42Blue" color2="suite42Green" :height="2" />
      <div class="flex flex-row">
        <SingleConnectionConnector color1="suite42Blue" color2="suite42Green" color3="suite42Green" :height="uploadFieldConnector" />
        <UploadField button-text="Upload new avatar" :file="regAvatarFile" label="Change avatar" @change="onRegAvatarChange" />
      </div>
      <DoubleConnectors color1="suite42Blue" color2="suite42Green" :height="2" />
      <div class="flex flex-row">
        <SingleEndConnectors color1="suite42Blue" color2="suite42Green" :height2="uploadFieldConnector" />
        <UploadField button-text="Upload new banner" :file="regBannerFile" label="Change banner" @change="onRegBannerChange" />
      </div>
      <SingleConnector color="suite42Blue" :height="4" />
      <div class="flex flex-row ">
        <ConnectConnector color1="suite42Blue" color2="suite42Red" :height="titleConnector" />
        <h3
          class="font-semibold font-h3-mobile
                 md:font-h3-tablet
                 lg:font-h3-laptop
                 xl:font-h3-desktop"
        >Security</h3>
      </div>
      <DoubleConnectors color1="suite42Red" color2="suite42Blue" :height="1" />
      <div class="flex flex-row">
        <SingleEndConnectors color1="suite42Red" color2="suite42Blue" :height2="inputFieldConnector" />
        <div class="flex flex-row gap-2">
          <input v-model="twoFaEnabled" class="w-5 h-5 cursor-pointer mt-1" type="checkbox">
          <div class="flex flex-col gap-0.5">
            <span
              class="font-regular font-h5-mobile
                       md:font-h5-tablet
                       lg:font-h5-laptop
                       xl:font-h5-desktop"
              :style="{ color: colors.suite42Black }"
            >Enable two-factor authentication (2FA via email)</span>
            <p
              class="font-regular font-body2-mobile
                       md:font-body2-tablet
                       lg:font-body2-laptop
                       xl:font-body2-desktop"
              :style="{ color: colors.suite42Darkgrey }"
            >When enabled, a one-time code will be sent to your email at each login.</p>
          </div>
        </div>
      </div>
      <SingleConnector color="suite42Red" :height="4" />
      <div class="flex flex-row">
        <ConnectConnector color1="suite42Red" color2="suite42Red" :height="connectorHeight2" />
        <InputField v-model="confirmPassword" label="CONFIRM PASSWORD" placeholder="Your current password" type="password" />
      </div>
      <SingleConnector color="suite42Red" :height="2" />
      <div class="flex flex-row">
        <EndConnector color="suite42Red" :height="connectorHeight2" />
        <div class="flex flex-col gap-4 items-start">
          <div class="flex flex-row gap-12 items-center">
            <SmallRedButton :disabled="isSaving" text="Save changes" @click="saveChangesRegular" />
            <RouterLink
              class="font-regular font-body2-mobile hover:underline
                     md:font-body2-tablet
                     lg:font-body2-laptop
                     xl:font-body2-desktop"
              :style="{ color: colors.suite42Black }"
              to="/profile"
            >Cancel</RouterLink>
          </div>
          <div class="min-h-12">
            <p
              v-if="saveError || saveSuccess || isSaving"
              class="font-regular font-h5-mobile
                     md:font-h5-tablet
                     lg:font-h5-laptop
                     xl:font-h5-desktop"
              :style="{
                color: saveError ? colors.suite42Red : isSaving ? colors.suite42Black : colors.suite42Green
              }"
            >{{ saveError || (isSaving ? 'Uploading...' : 'Profile updated!') }}</p>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
