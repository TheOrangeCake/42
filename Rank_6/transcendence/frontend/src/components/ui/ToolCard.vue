<script setup lang="ts">
  import { viewportValue } from '@/composables/viewportsValue.ts'
  import { colors, type Colors } from '@/styles/Colors'

  const toolCardProps = defineProps<{
    title: string
    text: string
    colors1: Colors
    colors2: Colors
    colors3: Colors
    image: string
  }>()

  const height1 = viewportValue({
    mobile: 1.2,
    tablet: 1.7,
    laptop: 1.7,
    desktop: 2,
  })

  const height2 = viewportValue({
    mobile: 0.9,
    tablet: 1,
    laptop: 1,
    desktop: 1,
  })
</script>

<template>
  <div class="flex flex-row">
    <SingleConnectionConnector :color1="toolCardProps.colors1" :color2="toolCardProps.colors2" :color3="toolCardProps.colors3" :height="height1" />
    <div
      class="flex flex-col w-full
             xl:w-2/3"
    >
      <h3
        class="font-medium font-h3-mobile
               md:font-h3-tablet
               lg:font-h3-laptop
               xl:font-h3-desktop"
        :style="{ color: colors.suite42Black }"
      >{{ toolCardProps.title }}</h3>
      <SingleConnector :color="toolCardProps.colors2" :height="1" />
      <div class="flex flex-row">
        <ConnectConnector :color1="toolCardProps.colors2" :color2="toolCardProps.colors2" :height="height2" />
        <p
          class="font-regular font-body1-mobile
               md:font-body1-tablet
               lg:font-body1-laptop
               xl:font-body1-desktop"
          :style="{ color: colors.suite42Black }"
        >{{ toolCardProps.text }}</p>
      </div>
      <SingleConnector :color="toolCardProps.colors2" :height="1" />
      <div class="flex flex-row w-full">
        <div class="flex grow">
          <EndConnector :color="toolCardProps.colors2" :full-width="true" :height="2" />
        </div>
        <div class="flex shrink">
          <img alt="" class="w-70 md:w-100 lg:w-115 xl:w-150 rounded-lg" :src="toolCardProps.image">
        </div>
      </div>
    </div>
  </div>
</template>
