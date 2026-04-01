<script setup lang="ts">
  import { colors } from '@/styles/Colors.ts'

  defineProps<{
    label: string
    active: boolean
    count?: number
  }>()

  defineEmits<{
    click: []
  }>()
</script>

<template>
  <button
    class="w-full px-4 py-2 rounded border-2 transition-colors cursor-pointer font-regular font-body1-mobile
           md:font-body1-tablet
           lg:font-body1-laptop
           xl:font-body1-desktop"
    :style="{
      color: active ? colors.suite42Blue : colors.suite42Darkgrey,
      borderColor: active ? colors.suite42Blue : colors.suite42Grey
    }"
    @click="$emit('click')"
  ><strong>{{ label }}</strong> ({{ count }})</button>
</template>
