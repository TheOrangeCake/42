<script setup lang="ts">
  import { type Colors, colors } from '@/styles/Colors.ts'

  const bigRedButtonProps = withDefaults(
    defineProps<{
      text: string
      hoverTextColor?: Colors
      type?: 'submit' | 'reset' | 'button'
    }>(),
    {
      hoverTextColor: 'suite42Black',
      type: 'button',
    },
  )

  const isHovered = ref(false)
  const emit = defineEmits(['click'])
</script>

<template>
  <div class="flex justify-center items-center cursor-pointer">
    <button
      class="flex px-5 py-2.5 justify-center items-center rounded border-2 font-medium font-h4-mobile transition-colors duration-200
             md:font-h4-tablet
             lg:font-h4-laptop
             xl:font-h4-desktop"
      :style="{
        borderColor: colors.suite42Red,
        backgroundColor: isHovered ? 'transparent' : colors.suite42Red,
        color: isHovered ? colors[bigRedButtonProps.hoverTextColor] : colors.suite42White
      }"
      :type="bigRedButtonProps.type"
      @click="emit('click')"
      @mouseleave="isHovered = false"
      @mouseover="isHovered = true"
    >
      {{ bigRedButtonProps.text }}
    </button>
  </div>
</template>
