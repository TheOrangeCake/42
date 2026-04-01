<script setup lang="ts">
  import type { Colors } from '@/styles/Colors'

  const connectConnectorProps = defineProps<{
    height: number
    color1: Colors
    color2: Colors
  }>()
</script>

<template>
  <div
    class="flex flex-col gap-2 self-stretch
              md:gap-4"
  >
    <EndConnector :color="connectConnectorProps.color1" :height="connectConnectorProps.height" />
    <SingleConnector
      class="flex-1"
      :color="connectConnectorProps.color2"
    />
  </div>
</template>
