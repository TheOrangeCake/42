<script setup lang="ts">
  import { useRouter } from 'vue-router'
  import { useAuthStore } from '../stores/auth'

  const authStore = useAuthStore()
  const router = useRouter()

  async function handleLogout () {
    await authStore.logout()
    router.push('/login')
  }
</script>

<template>
  <div
    class="flex flex-row justify-between pt-10 pb-4 px-4 items-center
         md:px-8
         lg:px-12
         xl:px-16
         2xl:px-24"
  >
    <RouterLink class="flex" to="/">
      <img
        alt="Suite 42 logo"
        class="h-12 w-auto xl:h-16"
        src="/design/assets/logo/logo_full.svg"
      >
    </RouterLink>

    <div
      class="flex flex-row gap-4 items-center
             md:gap-8"
    >
<!--      <PublicNavLink color="suite42Black" label="Campuses" link="/campuses" />-->

      <!-- Si connecté : affiche username + logout -->
      <template v-if="authStore.isLoggedIn">
        <SmallRedButton
          class="w-full md:w-auto"
          text="Sign out"
          @click="handleLogout"
        />
      </template>

      <!-- Si pas connecté : affiche Sign in -->
      <BigRedButton
        v-else
        class="w-full md:w-auto"
        text="Sign in"
        @click="router.push('/login')"
      />
    </div>
  </div>
</template>
