<script setup lang="ts">
  import type { Colors } from '@/styles/Colors'

  const singleConnectConnectorProps = defineProps<{
    height: number
    color1: Colors
    color2: Colors
    color3: Colors
  }>()
</script>

<template>
  <div
    class="flex flex-row gap-2
           md:gap-4"
  >
    <SingleConnector :color="singleConnectConnectorProps.color1" />
    <ConnectConnector :color1="singleConnectConnectorProps.color2" :color2="singleConnectConnectorProps.color3" :height="singleConnectConnectorProps.height" />
  </div>
</template>
