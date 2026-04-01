<script setup lang="ts">
  import type { Colors } from '@/styles/Colors.ts'

  const singleEndConnectorsProps = defineProps<{
    height1?: number
    height2: number
    color1: Colors
    color2: Colors
  }>()
</script>

<template>
  <div
    class="flex flex-row gap-2
           md:gap-4"
  >
    <SingleConnector :color="singleEndConnectorsProps.color1" :height="singleEndConnectorsProps.height1" />
    <EndConnector :color="singleEndConnectorsProps.color2" :height="singleEndConnectorsProps.height2" />
  </div>
</template>
