<script setup lang="ts">
  import { ref } from 'vue'
  import { useRouter } from 'vue-router'
  import { viewportValue } from '@/composables/viewportsValue'
  import { colors } from '@/styles/Colors'

  const emit = defineEmits(['login', 'login42'])
  const username = ref('')
  const password = ref('')

  const loginSectionProps = defineProps<{
    isLoading?: boolean
    errorMessage?: string
  }>()

  function handleLogin () {
    emit('login', { username: username.value, password: password.value })
  }

  const router = useRouter()
  const connectorHeight1 = viewportValue({
    mobile: 1.3,
    tablet: 1.5,
    laptop: 1.7,
    desktop: 2.2,
  })
  const connectorHeight2 = viewportValue({
    mobile: 1.4,
    tablet: 1.5,
    laptop: 1.5,
    desktop: 1.5,
  })
  const connectorHeight3 = viewportValue({
    mobile: 1.4,
    tablet: 1.5,
    laptop: 1.8,
    desktop: 1.9,
  })
  const connectorHeight4 = viewportValue({
    mobile: 1.5,
    tablet: 1.6,
    laptop: 1.6,
    desktop: 1.6,
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
    >Let's get productive !</h1>
    <div
      class="flex flex-col flex-wrap w-full gap-10
             xl:flex-row xl:gap-0 xl:mb-50"
    >
      <div class="flex flex-col">
        <SingleConnector color="suite42Red" :height="2" />
        <div class="flex flex-row">
          <ConnectConnector color1="suite42Red" color2="suite42Blue" :height="connectorHeight1" />
          <h3
            class="font-medium font-h3-mobile
                   md:font-h3-tablet
                   lg:font-h3-laptop
                   xl:font-h3-desktop"
          >Student 42 login</h3>
        </div>
        <DoubleConnectors color1="suite42Blue" color2="suite42Red" :height="1" />
        <div class="flex flex-row">
          <SingleEndConnectors color1="suite42Blue" color2="suite42Red" :height2="connectorHeight2" />
          <OauthButton
            image="/design/assets/icons/42_Logo.svg.png"
            text="Login with 42 account"
            @click="emit('login42')"
          />
        </div>
        <SingleConnector color="suite42Blue" :height="6" />
        <form @submit.prevent="handleLogin">
          <div class="flex flex-row">
            <ConnectConnector color1="suite42Blue" color2="suite42Background" :height="connectorHeight1" />
            <h3
              class="font-medium font-h3-mobile
                     md:font-h3-tablet
                     lg:font-h3-laptop
                     xl:font-h3-desktop"
            >Regular user login</h3>
          </div>
          <DoubleConnectors color1="suite42Background" color2="suite42Blue" :height="2" />
          <div class="flex flex-row">
            <SingleConnectionConnector color1="suite42Background" color2="suite42Blue" color3="suite42Blue" :height="connectorHeight3" />
            <InputField
              v-model="username"
              label="LOGIN"
              placeholder="pookie42"
              tooltip="username or email"
              type="text"
            />
          </div>
          <DoubleConnectors color1="suite42Background" color2="suite42Blue" :height="2" />
          <div class="flex flex-row">
            <SingleConnectionConnector color1="suite42Background" color2="suite42Blue" color3="suite42Blue" :height="connectorHeight3" />
            <InputField v-model="password" label="PASSWORD" type="password" />
          </div>
          <DoubleConnectors color1="suite42Background" color2="suite42Blue" :height="4" />
          <div class="flex flex-row">
            <SingleConnectionConnector color1="suite42Background" color2="suite42Blue" color3="suite42Green" :height="connectorHeight3" />
            <div
              class="flex flex-col gap-4 items-start"
            >
              <BigRedButton :disabled="loginSectionProps.isLoading" text="Sign in" type="submit" />
              <div class="min-h-12">
                <p
                  v-if="loginSectionProps.isLoading"
                  class="font-regular font-h5-mobile
                         md:font-h5-tablet
                         lg:font-h5-laptop
                         xl:font-h5-desktop"
                  :style="{ color: colors.suite42Black }"
                >Signing in ...</p>
                <p
                  v-if="loginSectionProps.errorMessage"
                  class="font-regular font-h5-mobile
                         md:font-h5-tablet
                         lg:font-h5-laptop
                         xl:font-h5-desktop"
                  :style="{ color: colors.suite42Red }"
                >{{ loginSectionProps.errorMessage }}</p>
              </div>
            </div>
          </div>
        </form>
        <DoubleConnectors color1="suite42Background" color2="suite42Green" :height="6" />
        <div class="flex flex-row">
          <SingleEndConnectors color1="suite42Background" color2="suite42Green" :height2="connectorHeight4" />
          <div class="flex flex-row gap-2 items-center">
            <p
              class="font-regular font-h5-mobile
                      md:font-h5-tablet
                      lg:font-h5-laptop
                      xl:font-h5-desktop"
              :style="{ color: colors.suite42Darkgrey }"
            >No account ?</p>
            <SmallBlueButton text="Create new account" @click="router.push('/signup')" />
          </div>
        </div>
      </div>
      <div class="flex grow justify-end">
        <img alt="" class="w-75 md:w-100 lg:w-120 lg:h-120 xl:w-150 xl:h-150" src="/design/assets/images/sign_in_illustration.png">
      </div>
    </div>
  </section>
</template>
