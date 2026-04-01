import { useRouter } from 'vue-router'
import { refreshToken, getMe42 } from '../api/auth'
import { useAuthStore } from '../stores/auth'

/**
 * Handles authentication initialization on app startup.
 * Runs immediately in setup (not onMounted) so the router guard's watch
 * on authReady can resolve before navigation completes.
 */
export function useAuthInit() {
  const authStore = useAuthStore()
  const router = useRouter()

  ;(async () => {
    try {
      authStore.loadFromStorage()
      if (authStore.accessToken) {
        const user = await refreshToken()
        const token = authStore.accessToken
        if (!token) throw new Error('No access token received after refresh')
        authStore.setSession(user, token)
      } else {
        await tryRestore42Session(authStore, router)
      }
    } catch {
      await tryRestore42Session(authStore, router)
    } finally {
      authStore.setAuthReady()
    }
  })()
}

async function tryRestore42Session(
  authStore: ReturnType<typeof useAuthStore>,
  router: ReturnType<typeof useRouter>,
) {
  try {
    const me = await getMe42()
    if (me.authenticated) {
      authStore.setSession42({ login: me.sub }, me.token)
      if (window.location.pathname === '/') {
        router.push('/home')
      }
    } else {
      authStore.clearSession()
    }
  } catch (e) {
    console.error('[auth] Failed to restore session:', e)
    authStore.clearSession()
  }
}
