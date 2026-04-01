<script setup lang="ts">
  import { onMounted, ref } from 'vue'
  import { useRouter } from 'vue-router'
  import { viewportValue } from '@/composables/viewportsValue.ts'
  import { colors } from '@/styles/Colors.ts'
  import { getUserProfile } from '../api/api42'
  import { useAuthStore } from '../stores/auth'

  const authStore = useAuthStore()
  const randomProject = ref<string | null>(null)
  const router = useRouter()

  onMounted(async () => {
    if (authStore.isRegularUser) return
    try {
      const profile = await getUserProfile()
      const eligible = profile.eligible_projects
      if (eligible && eligible.length > 0) {
        randomProject.value = eligible[Math.floor(Math.random() * eligible.length)] || ''
      }
    } catch {
    // Not a 42 user or API unavailable
    }
  })

  definePage({
    meta: {
      requiresAuth: true,
      layout: 'dashboard',
    },
  })
  const textConnector = viewportValue({
    mobile: 0.8,
    tablet: 1.1,
    laptop: 1,
    desktop: 1.1,
  })
  const buttonConnector = viewportValue({
    mobile: 1.2,
    tablet: 1.4,
    laptop: 1.6,
    desktop: 1.8,
  })
</script>

<template>
  <div
    class="flex flex-col w-full px-4 mb-20 mt-28
           md:mt-12
           lg:px-8 lg:mb-48
           xl:px-18
           2xl:px-28"
  >
    <div v-if="authStore.user42">
      <h1
        class="font-bold font-h1-mobile leading-12
             md:font-h1-tablet md:leading-16
             lg:font-h1-laptop lg:leading-24
             xl:font-h1-desktop"
        :style="{ color: colors.suite42Black }"
      >Hello, {{ authStore.user42?.login }}</h1>
      <h4
        class="font-semibold font-h4-mobile
             md:font-h4-tablet
             lg:font-h4-laptop
             xl:font-h4-desktop"
        :style="{ color: colors.suite42Darkgrey }"
      >How are you today?</h4>
      <SingleConnector color="suite42Blue" :height="3" />
      <div class="flex flex-row">
        <ConnectConnector color1="suite42Blue" color2="suite42Green" :height="textConnector" />
        <p
          v-if="randomProject"
          class="font-regular font-body1-mobile
             md:font-body1-tablet
             lg:font-body1-laptop
             xl:font-body1-desktop"
          :style="{ color: colors.suite42Black }"
        >You still haven't done project <strong>{{ randomProject }}</strong> yet.</p>
        <p
          v-else
          class="font-regular font-body1-mobile
             md:font-body1-tablet
             lg:font-body1-laptop
             xl:font-body1-desktop"
          :style="{ color: colors.suite42Black }"
        >Peer learning is the core philosophy of 42 and nothing beat group learning for this! Let's look for peers to progress together.</p>
      </div>
      <DoubleConnectors color1="suite42Green" color2="suite42Blue" :height="1" />
      <div class="flex flex-row">
        <SingleEndConnectors color1="suite42Green" color2="suite42Blue" :height2="buttonConnector" />
        <SmallRedButton text="Look for that special someone" @click="router.push('/finder')" />
      </div>
      <SingleConnector color="suite42Green" :height="4" />
      <div class="flex flex-row">
        <EndConnector color="suite42Green" :height="textConnector" />
        <p
          class="font-regular font-body1-mobile
                   md:font-body1-tablet
                   lg:font-body1-laptop
                   xl:font-body1-desktop"
          :style="{ color: colors.suite42Black }"
        >Or do you want to discuss project with friends instead?</p>
      </div>
      <DoubleConnectors color1="suite42Background" color2="suite42Green" :height="1" />
      <div class="flex flex-row">
        <SingleEndConnectors color1="suite42Background" color2="suite42Green" :height2="buttonConnector" />
        <SmallBlueButton text="Chat with friends" @click="router.push('/chat')" />
      </div>
    </div>
    <div v-else-if="authStore.user">
      <h1
        class="font-bold font-h1-mobile leading-12
             md:font-h1-tablet md:leading-16
             lg:font-h1-laptop lg:leading-24
             xl:font-h1-desktop"
        :style="{ color: colors.suite42Black }"
      >Hello, {{ authStore.user?.username }}</h1>
      <h4
        class="font-semibold font-h4-mobile
             md:font-h4-tablet
             lg:font-h4-laptop
             xl:font-h4-desktop"
        :style="{ color: colors.suite42Darkgrey }"
      >How are you today?</h4>
      <SingleConnector color="suite42Blue" :height="3" />
      <div class="flex flex-row">
        <EndConnector color="suite42Blue" :height="textConnector" />
        <p
          class="font-regular font-body1-mobile
                   md:font-body1-tablet
                   lg:font-body1-laptop
                   xl:font-body1-desktop"
          :style="{ color: colors.suite42Black }"
        >Tools that are destined for non 42 students are coming soon. Stay tuned!</p>
      </div>
    </div>
    <div class="flex grow justify-end">
      <img alt="" class="w-75 md:w-100 lg:w-120 lg:h-120 xl:w-150 xl:h-150" src="/design/assets/images/intra_home_illustration.png">
    </div>
  </div>
</template>
