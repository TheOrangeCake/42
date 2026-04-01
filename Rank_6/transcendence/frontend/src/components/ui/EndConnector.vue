<script setup lang="ts">
  import { viewportValue } from '@/composables/viewportsValue'
  import { colors, type Colors } from '@/styles/Colors'

  const endConnectorProps = withDefaults(defineProps<{
    height: number
    fullWidth?: boolean
    color: Colors
  }>(), { fullWidth: false })

  const connectorWidth = viewportValue({
    mobile: 1,
    tablet: 1.5,
    laptop: 2,
    desktop: 2,
  })
</script>

<template>
  <div
    class="flex items-center pl-3 pr-2
           md:pl-4
           xl:pl-4"
    :style="{
      height: `${endConnectorProps.height}rem`,
      width: endConnectorProps.fullWidth ? '100%' : undefined
    }"
  >
    <div
      class="border-l-[0.2rem] border-b-[0.2rem] h-full
             md:border-l-[0.3rem] md:border-b-[0.3rem]"
      :style="{
        borderColor: colors[endConnectorProps.color],
        width: endConnectorProps.fullWidth ? '100%' : `${connectorWidth}rem`
      }"
    />
  </div>
</template>
