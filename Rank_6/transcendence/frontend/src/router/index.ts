/**
 * router/index.ts
 *
 * Automatic routes for `./src/pages/*.vue`
 */

import { setupLayouts } from 'virtual:generated-layouts'
// Composables
import { createRouter, createWebHistory } from 'vue-router'
import { routes } from 'vue-router/auto-routes'
import { useAuthStore } from '@/stores/auth'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: setupLayouts(routes),
  scrollBehavior () {
    return { top: 0 }
  },
})

router.beforeEach(async to => {
  const auth = useAuthStore()
  if (!auth.authReady) {
    await new Promise<void>(resolve => {
      const unwatch = watch(
        () => auth.authReady,
        ready => {
          if (ready) {
            unwatch()
            resolve()
          }
        },
      )
    })
  }
  if (to.meta.requiresAuth && !auth.isLoggedIn) {
    return '/login'
  }
})

export default router
