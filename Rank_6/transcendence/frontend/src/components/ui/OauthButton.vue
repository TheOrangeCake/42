<script setup lang="ts">
  import { colors } from '@/styles/Colors.ts'

  const oauthButtonProps = defineProps<{
    image: string
    text: string
  }>()

  const isHovered = ref(false)
  const emit = defineEmits(['click'])
</script>

<template>
  <div class="flex justify-center items-center">
    <div
      class="flex px-12 py-1 justify-center items-center rounded border-2 font-medium font-body1-mobile cursor-pointer
             md:font-body1-tablet
             lg:font-body1-laptop
             xl:font-body1-desktop"
      :style="{
        borderColor: isHovered ? colors.suite42Red : colors.suite42Grey,
        backgroundColor: colors.suite42White,
        color: colors.suite42Black,
      }"
      @click="emit('click')"
      @mouseleave="isHovered = false"
      @mouseover="isHovered = true"
    >
      <img alt="" class="h-8 pr-6" :src="oauthButtonProps.image">
      {{ oauthButtonProps.text }}
    </div>
  </div>
</template>
