<script setup lang="ts">
  import type { User42 } from '@/api/api42'
  import { viewportValue } from '@/composables/viewportsValue.ts'
  import { colors } from '@/styles/Colors.ts'

  const finderProfileCardProps = defineProps<{
    user: User42
    recommendProject?: string
  }>()

  const scoreColor = computed(() => {
    const performanceScore = finderProfileCardProps.user.performance_score
    if (performanceScore >= 70) {
      return colors.suite42Green
    }
    if (performanceScore >= 40) {
      return colors.suite42Blue
    }
    return colors.suite42Black
  })

  const isHovered = ref(false)
  const emit = defineEmits(['click'])

  const titleConnector = viewportValue({
    mobile: 0.8,
    tablet: 1.1,
    laptop: 1,
    desktop: 1.1,
  })
  const itemConnector = viewportValue({
    mobile: 0.8,
    tablet: 1.1,
    laptop: 1,
    desktop: 1.1,
  })
  const buttonConnector = viewportValue({
    mobile: 0.8,
    tablet: 1.1,
    laptop: 1,
    desktop: 1.1,
  })
</script>

<template>
  <div
    class="flex flex-col px-4 pt-4 pb-12 border-1 rounded w-full"
    :style="{
      borderColor: isHovered ? colors.suite42Blue : colors.suite42Grey
    }"
    @mouseleave="isHovered = false"
    @mouseover="isHovered = true"
  >
    <div class="flex flex-row gap-4 mb-2 w-full">
      <div
        class="aspect-square shrink-0 w-44
               md:w-28
               lg:w-44"
      >
        <img
          alt="finderProfileCardProps.user.login"
          class="object-cover w-full h-full rounded"
          :src="finderProfileCardProps.user.custom_avatar_url || finderProfileCardProps.user.image?.versions?.medium || '/design/assets/images/other_user_avatar_cropped.jpg'"
        >
      </div>
      <div class="flex flex-col justify-between w-full">
        <div class="flex flex-row items-center justify-end w-full">
          <span
            v-if="finderProfileCardProps.recommendProject"
            class="font-regular font-h5-mobile
                   md:font-h5-tablet
                   lg:font-h5-laptop
                   xl:font-h5-desktop"
            :style="{ color: colors.suite42Red }"
          >Recommended for <strong>{{ finderProfileCardProps.recommendProject }}</strong></span>
          <div
            class="p-2 rounded font-bold font-h3-mobile
                   md:font-h3-tablet
                   lg:font-h3-laptop
                   xl:font-h3-desktop"
            :style="{
              backgroundColor: scoreColor,
              color: colors.suite42White
            }"
          >
            {{ finderProfileCardProps.user.performance_score }}
          </div>
        </div>
        <div class="flex flex-col">
          <h5
            class="font-semibold font-h4-mobile
                   md:font-h4-tablet
                   lg:font-h4-laptop
                   xl:font-h4-desktop"
            :style="{ color: colors.suite42Black }"
          >
            {{ finderProfileCardProps.user.first_name }} {{ finderProfileCardProps.user.last_name }}
          </h5>
          <p
            class="font-regular font-body1-mobile
                   md:font-body1-tablet
                   lg:font-body1-laptop
                   xl:font-body1-desktop"
            :style="{ color: colors.suite42Darkgrey }"
          >{{ finderProfileCardProps.user.login }}</p>
        </div>
      </div>
    </div>
    <SingleConnector color="suite42Blue" :height="2" />
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Blue" color2="suite42Green" :height="titleConnector" />
      <h5
        class="font-regular font-h4-mobile
               md:font-h4-tablet
               lg:font-h4-laptop
               xl:font-h4-desktop"
        :style="{ color: colors.suite42Black }"
      >Personal</h5>
    </div>
    <div class="flex flex-row">
      <SingleEndConnectors color1="suite42Green" color2="suite42Blue" :height2="itemConnector" />
      <p
        class="font-regular font-body1-mobile
        md:font-body1-tablet
        lg:font-body1-laptop
        xl:font-body1-desktop"
        :style="{ color: colors.suite42Black }"
      >Intranet:
        <a
          class="font-font-regular font-body1-mobile hover:underline
                   md:font-body1-tablet
                   lg:font-body1-laptop
                   xl:font-body1-desktop"
          :href="finderProfileCardProps.user.intra_url"
          rel="noopener noreferrer"
          :style="{ color: colors.suite42Blue }"
          target="_blank"
        ><strong>{{ finderProfileCardProps.user.login }}</strong></a>
      </p>

    </div>
    <div class="flex flex-row">
      <SingleEndConnectors color1="suite42Green" color2="suite42Blue" :height2="itemConnector" />
      <p
        class="font-regular font-body1-mobile
        md:font-body1-tablet
        lg:font-body1-laptop
        xl:font-body1-desktop"
        :style="{ color: colors.suite42Black }"
      >Pool: {{ finderProfileCardProps.user.pool_month }} {{ finderProfileCardProps.user.pool_year }}</p>
    </div>
    <SingleConnector color="suite42Green" :height="1" />
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Green" color2="suite42Red" :height="titleConnector" />
      <h5
        class="font-regular font-h4-mobile
               md:font-h4-tablet
               lg:font-h4-laptop
               xl:font-h4-desktop"
        :style="{ color: colors.suite42Black }"
      >Common Core</h5>
    </div>
    <div class="flex flex-row">
      <SingleEndConnectors color1="suite42Red" color2="suite42Green" :height2="itemConnector" />
      <p
        class="font-regular font-body1-mobile
        md:font-body1-tablet
        lg:font-body1-laptop
        xl:font-body1-desktop"
        :style="{ color: colors.suite42Black }"
      >Rank: {{ finderProfileCardProps.user.rank }}</p>
    </div>
    <div class="flex flex-row">
      <SingleEndConnectors color1="suite42Red" color2="suite42Green" :height2="itemConnector" />
      <p
        class="font-regular font-body1-mobile
        md:font-body1-tablet
        lg:font-body1-laptop
        xl:font-body1-desktop"
        :style="{ color: colors.suite42Black }"
      >Rank progress: {{ finderProfileCardProps.user.rank_progress_percent }}%</p>
    </div>
    <SingleConnector color="suite42Red" :height="2" />
    <div class="flex flex-row">
      <EndConnector color="suite42Red" :height="buttonConnector" />
      <SmallRedButton :text="'View profile'" @click="emit('click')" />
    </div>
  </div>
</template>
