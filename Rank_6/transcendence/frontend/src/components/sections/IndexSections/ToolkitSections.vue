<script setup lang="ts">
  import { useRouter } from 'vue-router'
  import { viewportValue } from '@/composables/viewportsValue'
  import { colors } from '@/styles/Colors.ts'

  const router = useRouter()
  const connectorHeight1 = viewportValue({
    mobile: 1.7,
    tablet: 2.2,
    laptop: 2.5,
    desktop: 3.8,
  })
  const connectorHeight2 = viewportValue({
    mobile: 1.6,
    tablet: 1.7,
    laptop: 1.8,
    desktop: 2,
  })
</script>

<template>
  <section
    class="flex flex-col w-full px-6
           md:px-10
           lg:px-14
           xl:px-18
           2xl:px-28"
  >
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Green" color2="suite42Red" :height="connectorHeight1" />
      <h1
        class="font-bold font-h1-mobile
               md:font-h1-tablet
               lg:font-h1-laptop
               xl:font-h1-desktop"
        :style="{ color: colors.suite42Black }"
      >Our toolkit</h1>
    </div>
    <DoubleConnectors color1="suite42Red" color2="suite42Blue" :height="2" />
    <ToolCard
      colors1="suite42Red"
      colors2="suite42Blue"
      colors3="suite42Green"
      image="/design/assets/placeholder/tool_section.jpg"
      text="Quickly search for compatible teammates and remove the friction of forming project groups."
      title="Teammates finder"
    />
    <DoubleConnectors color1="suite42Red" color2="suite42Green" :height="8" />
    <ToolCard
      colors1="suite42Red"
      colors2="suite42Green"
      colors3="suite42Red"
      image="/design/assets/placeholder/comingSoon.svg"
      text="Get structured guidance and explanations aligned with your current 42 project—without giving direct answers."
      title="AI project helper (coming soon)"
    />
    <DoubleConnectors color1="suite42Red" color2="suite42Red" :height="8" />
    <ToolCard
      colors1="suite42Red"
      colors2="suite42Red"
      colors3="suite42Black"
      image="/design/assets/placeholder/comingSoon.svg"
      text="Plan your tasks, follow your progress, and maintain momentum across your 42 projects."
      title="To do list (coming soon)"
    />
    <DoubleConnectors color1="suite42Red" color2="suite42Black" :height="8" />
    <ToolCard
      colors1="suite42Red"
      colors2="suite42Black"
      colors3="suite42Blue"
      image="/design/assets/placeholder/comingSoon.svg"
      text="Maintain deep focus, work efficiently and increase productivity with study session timer."
      title="Pomodoro session (coming soon)"
    />
    <DoubleConnectors color1="suite42Red" color2="suite42Blue" :height="8" />
    <div class="flex flex-row">
      <SingleEndConnectors color1="suite42Red" color2="suite42Blue" :height2="connectorHeight2" />
      <BigRedButton text="Let's start working !" @click="router.push('/login')" />
    </div>
    <SingleConnector color="suite42Red" :height="12" />
  </section>
</template>
