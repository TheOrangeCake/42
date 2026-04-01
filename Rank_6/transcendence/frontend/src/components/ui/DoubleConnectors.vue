<script setup lang="ts">
  import type { Colors } from '@/styles/Colors.ts'

  const doubleConnectorsProps = defineProps<{
    height?: number
    color1: Colors
    color2: Colors
  }>()
</script>

<template>
  <div
    class="flex flex-row gap-2
           md:gap-4"
  >
    <SingleConnector :color="doubleConnectorsProps.color1" :height="doubleConnectorsProps.height" />
    <SingleConnector :color="doubleConnectorsProps.color2" :height="doubleConnectorsProps.height" />
  </div>
</template>
