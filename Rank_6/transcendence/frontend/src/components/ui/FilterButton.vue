<script setup lang="ts">
  import { colors } from '@/styles/Colors.ts'

  const filterButtonProps = defineProps<{
    text: string
    icon: string
    alt: string
  }>()
  const isHovered = ref(false)
  const emit = defineEmits(['click'])
</script>

<template>
  <div class="flex justify-center items-center cursor-pointer">
    <button
      class="flex px-6 py-2 justify-center items-center rounded border-2 font-medium font-body1-mobile transition-colors duration-200
             md:font-body1-tablet
             lg:font-body1-laptop
             xl:font-body1-desktop"
      :style="{
        borderColor: colors.suite42Red,
        backgroundColor: isHovered ? colors.suite42Red : 'transparent',
        color: colors.suite42Black
      }"
      @click="emit('click')"
      @mouseleave="isHovered = false"
      @mouseover="isHovered = true"
    >
      <img
        :alt="filterButtonProps.alt"
        class="object-cover h-6 aspect-square mr-3"
        :src="filterButtonProps.icon"
      >
      {{ filterButtonProps.text }}
    </button>
  </div>
</template>
