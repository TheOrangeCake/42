import { useWindowSize } from '@vueuse/core'
import { computed } from 'vue'

export type Viewport = 'mobile' | 'tablet' | 'laptop' | 'desktop'

export function useViewports () {
  const { width } = useWindowSize()

  const currentViewport = computed<Viewport>(() => {
    if (width.value >= 1440) {
      return 'desktop'
    }
    if (width.value >= 1024) {
      return 'laptop'
    }
    if (width.value >= 768) {
      return 'tablet'
    }
    return 'mobile'
  })

  return { currentViewport }
}
