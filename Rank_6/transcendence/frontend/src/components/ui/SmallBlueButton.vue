<script setup lang="ts">
  import { type Colors, colors } from '@/styles/Colors.ts'

  const smallBlueButtonProps = defineProps<{
    text: string
    hoverTextColor?: Colors
    borderColor?: Colors
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
        borderColor: smallBlueButtonProps.borderColor? colors[smallBlueButtonProps.borderColor] : colors.suite42Blue,
        backgroundColor: isHovered ? (smallBlueButtonProps.borderColor ? colors[smallBlueButtonProps.borderColor] : colors.suite42Blue) : 'transparent',
        color: isHovered ? (smallBlueButtonProps.hoverTextColor ? colors[smallBlueButtonProps.hoverTextColor] : colors.suite42Black) : colors.suite42Black
      }"
      @click="emit('click')"
      @mouseleave="isHovered = false"
      @mouseover="isHovered = true"
    >
      {{ smallBlueButtonProps.text }}
    </button>
  </div>
</template>
