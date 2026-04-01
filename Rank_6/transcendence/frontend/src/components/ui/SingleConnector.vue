<script setup lang="ts">
  import { colors, type Colors } from '@/styles/Colors.ts'

  const singleConnectorProps = defineProps<{
    height?: number
    color: Colors
  }>()
</script>

<template>
  <div
    class="flex self-stretch items-center pl-3 pr-2
           md:pl-4
           xl:pl-4"
    :style="{
      height: singleConnectorProps.height !== undefined
        ? (`${singleConnectorProps.height}rem`)
        : undefined
    }"
  >
    <div
      class="border-l-[0.2rem] h-full
            md:border-l-[0.3rem]"
      :style="{ borderColor: colors[singleConnectorProps.color] }"
    />
  </div>
</template>
