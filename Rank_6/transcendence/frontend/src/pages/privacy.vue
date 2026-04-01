<script setup lang="ts">
  import { viewportValue } from '@/composables/viewportsValue.ts'
  import { colors } from '@/styles/Colors.ts'

  const titleConnector = viewportValue({
    mobile: 0.8,
    tablet: 0.9,
    laptop: 0.9,
    desktop: 0.9,
  })

  const textConnector = viewportValue({
    mobile: 1,
    tablet: 1.1,
    laptop: 1.4,
    desktop: 1.5,
  })
</script>

<template>
  <section
    class="flex flex-col w-full px-6 mb-20
           md:px-10
           lg:px-14
           xl:px-18
           2xl:px-64"
  >
    <h1
      class="font-bold font-h1-mobile leading-12
             md:font-h1-tablet md:leading-16
             lg:font-h1-laptop lg:leading-24
             xl:font-h1-desktop"
      :style="{ color: colors.suite42Black }"
    >Privacy Policy</h1>
    <SingleConnector color="suite42Blue" :height="1" />
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Blue" color2="suite42Green" :height="titleConnector" />
      <p
        class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
        :style="{ color: colors.suite42Black }"
      >
        This Privacy Policy explains how Suite42 ("we", "us", "our") collects, uses,
        and protects your personal data when you use our service.<br>

        By using the service, you agree to the collection and use of information in
        accordance with this policy. We may update this policy at any time. We
        encourage you to review it regularly.
      </p>
    </div>
    <SingleConnector color="suite42Green" :height="2" />
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Green" color2="suite42Red" :height="textConnector" />
      <div class="flex flex-col w-full">
        <h4
          class="font-semibold font-h4-mobile
             md:font-h4-tablet
             lg:font-h4-laptop
             xl:font-h4-desktop"
          :style="{ color: colors.suite42Black }"
        >What User Data We Collect</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          When you visit the website, we may collect the following data:
          <ul>
            <li>• Account information (such as username, email, first and last name).</li>
            <li>• Technical data (such as IP address and device information).</li>
            <li>• Usage data (such as interactions within the platform).</li>
            <li>• Messages and content exchanged between users.</li>
          </ul>
        </p>
      </div>
    </div>
    <SingleConnector color="suite42Red" :height="2" />
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Red" color2="suite42Black" :height="textConnector" />
      <div class="flex flex-col w-full">
        <h4
          class="font-semibold font-h4-mobile
             md:font-h4-tablet
             lg:font-h4-laptop
             xl:font-h4-desktop"
          :style="{ color: colors.suite42Black }"
        >Why We Collect Your Data</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          We are collecting your data for several reasons:
          <ul>
            <li>• To provide and maintain the service.</li>
            <li>• To enable communication between users.</li>
            <li>• To improve and optimize the platform.</li>
            <li>• To ensure security and prevent abuse.</li>
          </ul>
        </p>
      </div>
    </div>
    <SingleConnector color="suite42Black" :height="2" />
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Black" color2="suite42Blue" :height="textConnector" />
      <div class="flex flex-col w-full">
        <h4
          class="font-semibold font-h4-mobile
             md:font-h4-tablet
             lg:font-h4-laptop
             xl:font-h4-desktop"
          :style="{ color: colors.suite42Black }"
        >Safeguarding and Securing the Data</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          We take appropriate technical and organizational measures to protect your
          personal data against unauthorized access, loss, or misuse. However, no
          system can be completely secure, and we cannot guarantee absolute security.
        </p>
      </div>
    </div>
    <SingleConnector color="suite42Blue" :height="2" />
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Blue" color2="suite42Green" :height="textConnector" />
      <div class="flex flex-col w-full">
        <h4
          class="font-semibold font-h4-mobile
             md:font-h4-tablet
             lg:font-h4-laptop
             xl:font-h4-desktop"
          :style="{ color: colors.suite42Black }"
        >Our Cookie Policy</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          We use only essential cookies required for authentication and proper
          functioning of the service. These cookies are necessary and cannot be
          disabled without affecting the operation of the platform.
        </p>
      </div>
    </div>
    <SingleConnector color="suite42Green" :height="2" />
    <div class="flex flex-row">
      <EndConnector color="suite42Green" :height="textConnector" />
      <div class="flex flex-col w-full">
        <h4
          class="font-semibold font-h4-mobile
             md:font-h4-tablet
             lg:font-h4-laptop
             xl:font-h4-desktop"
          :style="{ color: colors.suite42Black }"
        >Restricting the Collection of your Personal Data</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          We do not sell or rent your personal data to third parties. We may disclose
          information if required by law or to protect the security and integrity of
          the service.<br>
          You have the right to access, correct, or delete your personal data. You may
          contact us to exercise these rights.
        </p>
      </div>
    </div>
  </section>
</template>
