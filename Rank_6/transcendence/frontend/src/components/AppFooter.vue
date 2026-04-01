<script setup lang="ts">
  import { useRouter } from 'vue-router'
  import { colors } from '@/styles/Colors.ts'

  const router = useRouter()
  const legalLinks = [
    { id: 1, label: 'Privacy Policy', link: '/privacy' },
    { id: 2, label: 'Terms of Service', link: '/tos' },
  ]
</script>

<template>
  <footer
    class="flex flex-col w-full py-10 px-6
         md:px-10
         lg:px-14
         xl:px-18
         2xl:px-28"
    :style="{ backgroundColor: colors.suite42Black }"
  >
    <div
      class="flex flex-col gap-12 items-center
             md:gap-0 md:flex-row md:justify-between md:items-center"
    >
      <BigRedButton
        class="w-full md:w-auto"
        hover-text-color="suite42White"
        path="/login"
        text="Let's get productive!"
        @click="router.push('/login')"
      />
      <RouterLink class="flex" to="/">
        <img
          alt="Suite 42 logo"
          class="h-16 w-auto md:h-20 lg:h-24 xl:h-32"
          src="/design/assets/logo/logo_full.svg"
        >
      </RouterLink>
    </div>

    <div class="border-t-2 mt-10 lg:mt-15 xl:mt-20" :style="{ borderColor: colors.suite42Red }" />
    <div class="flex flex-row gap-10 pt-5 justify-center">
      <div
        v-for="link in legalLinks"
        :key="link.id"
      >
        <a :href="link.link" class="text-white text-sm opacity-60 hover:opacity-100">{{ link.label }}</a>
      </div>
    </div>
  </footer>
</template>
