<script setup lang="ts">
  import { ref } from 'vue'
  import { viewportValue } from '@/composables/viewportsValue'
  import { colors } from '@/styles/Colors'
  const emit = defineEmits(['signup'])

  const username = ref('')
  const email = ref('')
  const password = ref('')
  const confirmPassword = ref('')
  const agreeToTerms = ref(false)

  const signupSectionProps = defineProps<{
    isLoading?: boolean
    errorMessage?: string
    successMessage?: string
  }>()

  function handleSignup () {
    emit('signup', {
      username: username.value,
      email: email.value,
      password: password.value,
      confirmPassword: confirmPassword.value,
      agreeToTerms: agreeToTerms.value,
    })
  }
  const connectorHeight1 = viewportValue({
    mobile: 1.3,
    tablet: 1.5,
    laptop: 1.7,
    desktop: 2.2,
  })
  const connectorHeight2 = viewportValue({
    mobile: 1.4,
    tablet: 1.5,
    laptop: 1.8,
    desktop: 1.9,
  })
  const connectorHeight3 = viewportValue({
    mobile: 0.8,
    tablet: 1.2,
    laptop: 1.2,
    desktop: 1.2,
  })
</script>

<template>
  <section
    class="flex flex-col w-full px-6
           md:px-10
           lg:px-14
           xl:px-28 xl:pt-16
           2xl:px-0 2xl:max-w-300 2xl:mx-auto"
  >
    <h1
      class="font-bold font-h1-mobile
               md:font-h1-tablet
               lg:font-h1-laptop
               xl:font-h1-desktop"
      :style="{ color: colors.suite42Black }"
    >Create new account</h1>
    <div
      class="flex flex-col flex-wrap w-full gap-10
             xl:flex-row xl:gap-0 xl:mb-50"
    >
      <form class="flex flex-col" @submit.prevent="handleSignup">
        <SingleConnector color="suite42Blue" :height="2" />
        <div class="flex flex-row">
          <ConnectConnector color1="suite42Blue" color2="suite42Background" :height="connectorHeight1" />
          <h3
            class="font-medium font-h3-mobile
                   md:font-h3-tablet
                   lg:font-h3-laptop
                   xl:font-h3-desktop"
            :style="{ color: colors.suite42Black }"
          >Credentials</h3>
        </div>
        <DoubleConnectors color1="suite42Background" color2="suite42Blue" :height="2" />
        <div class="flex flex-row">
          <SingleConnectionConnector color1="suite42Background" color2="suite42Blue" color3="suite42Blue" :height="connectorHeight2" />
          <InputField v-model="username" label="USERNAME" placeholder="pookie42" type="text" />
        </div>
        <DoubleConnectors color1="suite42Background" color2="suite42Blue" :height="2" />
        <div class="flex flex-row">
          <SingleConnectionConnector color1="suite42Background" color2="suite42Blue" color3="suite42Blue" :height="connectorHeight2" />
          <InputField v-model="email" label="EMAIL" placeholder="pookie42@proton.me" type="email" />
        </div>
        <DoubleConnectors color1="suite42Background" color2="suite42Blue" :height="2" />
        <div class="flex flex-row">
          <SingleConnectionConnector color1="suite42Background" color2="suite42Blue" color3="suite42Blue" :height="connectorHeight2" />
          <InputField v-model="password" label="PASSWORD" type="password" />
        </div>
        <DoubleConnectors color1="suite42Background" color2="suite42Blue" :height="2" />
        <div class="flex flex-row">
          <SingleConnectionConnector color1="suite42Background" color2="suite42Blue" color3="suite42Blue" :height="connectorHeight2" />
          <InputField v-model="confirmPassword" label="CONFIRM PASSWORD" type="password" />
        </div>
        <DoubleConnectors color1="suite42Background" color2="suite42Blue" :height="2" />
        <div class="flex flex-row">
          <SingleConnectionConnector color1="suite42Background" color2="suite42Blue" color3="suite42Blue" :height="connectorHeight3" />
          <div class="flex flex-row gap-2 items-center">
            <input v-model="agreeToTerms" class="w-5 h-5 cursor-pointer" type="checkbox">
            <span
              class="font-regular font-h5-mobile
                     md:font-h5-tablet
                     lg:font-h5-laptop
                     xl:font-h5-desktop"
              :style="{ color: colors.suite42Darkgrey }"
            >Agree to Terms of Service</span>
          </div>
        </div>
        <DoubleConnectors color1="suite42Background" color2="suite42Blue" :height="4" />
        <div class="flex flex-row">
          <SingleEndConnectors color1="suite42Background" color2="suite42Blue" :height2="connectorHeight2" />
          <div class="flex flex-col gap-4 items-start">
            <BigRedButton :disabled="signupSectionProps.isLoading" text="Sign up" type="submit" />
            <div class="min-h-12">
              <p
                v-if="signupSectionProps.isLoading"
                class="font-regular font-h5-mobile
                       md:font-h5-tablet
                       lg:font-h5-laptop
                       xl:font-h5-desktop"
                :style="{ color: colors.suite42Black }"
              >Creating your account ...</p>
              <p
                v-if="signupSectionProps.errorMessage"
                class="font-regular font-h5-mobile
                       md:font-h5-tablet
                       lg:font-h5-laptop
                       xl:font-h5-desktop"
                :style="{ color: colors.suite42Red }"
              >{{ signupSectionProps.errorMessage }}</p>
              <p
                v-if="signupSectionProps.successMessage"
                class="font-regular font-h5-mobile
                       md:font-h5-tablet
                       lg:font-h5-laptop
                       xl:font-h5-desktop"
                :style="{ color: colors.suite42Green }"
              >{{ signupSectionProps.successMessage }}</p>
            </div>
          </div>
        </div>
      </form>
      <div class="flex grow justify-end">
        <img alt="" class="w-75 md:w-100 lg:w-120 lg:h-120 xl:w-150 xl:h-150" src="/design/assets/images/sign_up_illustration.png">
      </div>
    </div>
  </section>
</template>
