<script setup lang="ts">
  import { colors, type Colors } from '@/styles/Colors.ts'

  const publicNavLinkProps = defineProps<{
    link: string
    label: string
    color: Colors
  }>()
</script>

<template>
  <div>
    <RouterLink :to="publicNavLinkProps.link">
      <span
        class="font-regular opacity-80 hover:opacity-100 hover:underline font-h5-mobile
                md:font-h5-tablet
                lg:font-h5-laptop
                xl:font-h5-desktop"
        :style="{ color: colors[publicNavLinkProps.color] }"
      >{{ publicNavLinkProps.label }}</span>
    </RouterLink>
  </div>
</template>
