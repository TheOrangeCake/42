<template>
  <v-app class="app-root">
    <Navbar v-if="!isDashboardRoute" />
    <router-view />
    <AppFooter v-if="!isDashboardRoute" />
  </v-app>
</template>

<script setup lang="ts">
  import { computed } from 'vue'
  import { useRoute } from 'vue-router'
  import { useAuthInit } from './composables/useAuthInit'

  const route = useRoute()

  const isDashboardRoute = computed(() =>
    route.meta.layout === 'dashboard',
  )

  useAuthInit()
</script>
