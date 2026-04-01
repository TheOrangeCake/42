<script setup lang="ts">
  import { viewportValue } from '@/composables/viewportsValue'
  import { colors } from '@/styles/Colors.ts'

  const connectorHeight1 = viewportValue({
    mobile: 2,
    tablet: 2.2,
    laptop: 2,
    desktop: 3.5,
  })
  const connectorHeight2 = viewportValue({
    mobile: 1,
    tablet: 1.1,
    laptop: 1,
    desktop: 1.1,
  })

  const teamMembers = [
    { id: 1, name: 'Alex', role: 'Frontend', img: '/design/assets/photo/alletond.jpg' },
    { id: 2, name: 'Vincent', role: 'Backend', img: '/design/assets/photo/vgomes.jpg' },
    { id: 3, name: 'Dan', role: 'Backend', img: '/design/assets/photo/dengelba.jpg' },
    { id: 4, name: 'Dimitri', role: 'Backend', img: '/design/assets/photo/dconza.jpg' },
    { id: 5, name: 'Nguyen', role: 'Full-stack', img: '/design/assets/photo/hoannguy.jpg' },
  ]
</script>

<template>
  <section
    class="flex flex-col w-full px-6
           md:px-10
           lg:px-14
           xl:px-18
           2xl:px-28"
    :style="{ backgroundColor: colors.suite42Black }"
  >
    <SingleConnector color="suite42Red" :height="6" />
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Red" color2="suite42Green" :height="connectorHeight1" />
      <h1
        class="font-bold font-h1-mobile
               md:font-h1-tablet
               lg:font-h1-laptop
               xl:font-h1-desktop"
        :style="{ color: colors.suite42White }"
      >About us</h1>
    </div>
    <DoubleConnectors color1="suite42Green" color2="suite42Blue" :height="2" />
    <div
      class="flex flex-row gap-2
             md:gap-4"
    >
      <SingleConnector color="suite42Green" />
      <div
        class="flex flex-col gap-30
               xl:flex-row"
      >
        <div
          class="flex flex-col
                 xl:w-full"
        >
          <div class="flex flex-row">
            <ConnectConnector color1="suite42Blue" color2="suite42Blue" :height="connectorHeight2" />
            <p
              class="font-regular font-body1-mobile
                   md:font-body1-tablet
                   lg:font-body1-laptop
                   xl:font-body1-desktop"
              :style="{ color: colors.suite42White }"
            >Suite42 is a ft_transcendence project by Alex, Vincent, Dan, Dimitri and Nguyen, from the 2023–2024 cohort at 42 Lausanne.</p>
          </div>
          <SingleConnector color="suite42Blue" :height="2" />
          <div class="flex flex-row">
            <ConnectConnector color1="suite42Blue" color2="suite42Blue" :height="connectorHeight2" />
            <p
              class="font-regular font-body1-mobile
                   md:font-body1-tablet
                   lg:font-body1-laptop
                   xl:font-body1-desktop"
              :style="{ color: colors.suite42White }"
            >We were not content with simply creating something for the sake of creating; we wanted our project to have a clear purpose and a reason to exist. The idea was first proposed by one of the team members, who had difficulty finding groups for many of his projects at 42. The initial concept was a group finder based on users’ progression in the Common Core. The team immediately supported the idea, as several members had encountered the same problem.</p>
          </div>
          <SingleConnector color="suite42Blue" :height="0.5" />
          <div class="flex flex-row">
            <ConnectConnector color1="suite42Blue" color2="suite42Blue" :height="connectorHeight2" />
            <p
              class="font-regular font-body1-mobile
                   md:font-body1-tablet
                   lg:font-body1-laptop
                   xl:font-body1-desktop"
              :style="{ color: colors.suite42White }"
            > After conducting research, we found that several websites already offer “group finder” features, but they are limited to simply displaying information. Our team decided to take this concept further by adding the ability to connect with other students, add friends, communicate directly, and use advanced filtering and sorting. We also implemented a recommendation system based on Common Core progression.</p>
          </div>
          <SingleConnector color="suite42Blue" :height="2" />
          <div class="flex flex-row">
            <EndConnector color="suite42Blue" :height="connectorHeight2" />
            <p
              class="font-regular font-body1-mobile
                   md:font-body1-tablet
                   lg:font-body1-laptop
                   xl:font-body1-desktop"
              :style="{ color: colors.suite42White }"
            > The project later evolved into a multi-purpose suite designed to support 42 students in successfully completing their Common Core.</p>
          </div>
        </div>
        <div class="flex flex-row gap-2 flex-wrap justify-center">
          <div v-for="member in teamMembers" :key="member.id" class="flex flex-col items-center">
            <img
              :alt="member.name"
              class="w-32 h-32 md:w-40 md:h-40 object-cover mb-2 rounded-lg"
              :src="member.img"
            >
            <p
              class="text-center font-semibold font-h4-mobile
                     md:font-h4-tablet
                     lg:font-h4-laptop
                     xl:font-h4-desktop"
              :style="{ color: colors.suite42White }"
            >{{ member.name }}</p>
            <p
              class="text-center font-regular font-body1-mobile
                     md:font-body1-tablet
                     lg:font-body1-laptop
                     xl:font-body1-desktop"
              :style="{ color: colors.suite42Grey }"
            >{{ member.role }}</p>
          </div>
        </div>
      </div>
    </div>
    <SingleConnector color="suite42Green" :height="12" />
  </section>
</template>
