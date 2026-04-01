<script setup lang="ts">
  import { viewportValue } from '@/composables/viewportsValue'
  import { colors } from '@/styles/Colors.ts'

  const connectorHeight1 = viewportValue({
    mobile: 2,
    tablet: 2.2,
    laptop: 2,
    desktop: 3.5,
  })
</script>

<template>
  <section
    class="flex flex-col w-full px-6 pb-50
           md:px-10
           lg:px-14
           xl:px-18 xl:pb-70
           2xl:px-28"
    :style="{ backgroundColor: colors.suite42Darkgrey }"
  >
    <SingleConnector color="suite42Red" :height="6" />
    <div class="flex flex-row">
      <EndConnector color="suite42Red" :height="connectorHeight1" />
      <div class="flex flex-col">
        <h1
          class="font-bold font-h1-mobile
                 md:font-h1-tablet
                 lg:font-h1-laptop
                 xl:font-h1-desktop"
          :style="{ color: colors.suite42White }"
        >Contact us</h1>
        <p
          class="font-regular font-body1-mobile
                  md:font-body1-tablet
                  lg:font-body1-laptop
                  xl:font-body1-desktop"
          :style="{ color: colors.suite42White }"
        >
          Bugs? Ideas? Feedback? Simply a chat? Contact us through our email: <br><br><strong>info.suite42@gmail.com</strong>
        </p>
      </div>
    </div>
  </section>
</template>
