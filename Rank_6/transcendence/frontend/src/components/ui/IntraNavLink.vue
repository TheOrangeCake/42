<script setup lang="ts">
  import { colors } from '@/styles/Colors.ts'

  const intraNavLinkProps = defineProps<{
    icon: string
    alt: string
    label: string
    link: string
    isAvatar: boolean
  }>()
  const isHovered = ref(false)
</script>

<template>
  <RouterLink
    class="flex flex-col w-full gap-1 items-center border-1 rounded px-2 py-2 transition-colors duration-200"
    :style="{
      borderColor: isHovered ? colors.suite42Darkgrey : colors.suite42Black,
    }"
    :to="intraNavLinkProps.link"
    @mouseleave="isHovered = false"
    @mouseover="isHovered = true"
  >
    <img
      :alt="intraNavLinkProps.alt"
      class="object-cover"
      :class="[
        intraNavLinkProps.isAvatar
          ? 'w-12 h-12 rounded-full'
          : 'w-12 h-12 md:w-6 md:h-6'
      ]"
      :src="intraNavLinkProps.icon"
    >
    <span
      class="font-regular font-body2-mobile
                   md:font-body2-tablet
                   lg:font-body2-laptop
                   xl:font-body2-desktop"
      :style="{
        color: isHovered ? colors.suite42White : colors.suite42Grey,
      }"
    >{{ intraNavLinkProps.label }}</span>
  </RouterLink>
</template>
