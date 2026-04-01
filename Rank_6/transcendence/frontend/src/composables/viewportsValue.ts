import { computed } from 'vue'
import { useViewports, type Viewport } from '@/composables/useViewports'

type ViewportMap<T> = Record<Viewport, T>

export function viewportValue<T> (values: ViewportMap<T>) {
  const { currentViewport } = useViewports()

  return computed(() => values[currentViewport.value])
}
