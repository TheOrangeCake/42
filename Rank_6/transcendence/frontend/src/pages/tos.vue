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
    >Terms of Service</h1>
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
        Effective Date: 23 March 2026
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
        >Acceptance of Terms</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          By accessing or using this website ("Service"), you agree to be bound by these Terms of Service. If you do not agree, you must not use the Service.
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
        >Description of Service</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          The Service provides:
          <ul>
            <li>• User authentication (account creation and login).</li>
            <li>• A directory of 42 Lausanne users.</li>
            <li>• Messaging functionality allowing users to communicate with each other.</li>
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
        >User Accounts</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          To use certain features, you must create an account. You agree to:
          <ul>
            <li>• Provide accurate and complete information.</li>
            <li>• Keep your login credentials secure.</li>
            <li>• Be responsible for all activity under your account.</li>
          </ul>
          We reserve the right to suspend or terminate accounts that violate these Terms.
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
        >Acceptable Use</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          You agree not to:
          <ul>
            <li>• Use the Service for unlawful purposes.</li>
            <li>• Harass, abuse, or harm other users.</li>
            <li>• Send spam or unsolicited messages.</li>
            <li>• Impersonate another person or entity.</li>
            <li>• Attempt to gain unauthorized access to the system.</li>
          </ul>
          We reserve the right to suspend or terminate accounts that violate these Terms.
        </p>
      </div>
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
        >User Content</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          Users may send messages and share information through the Service ("User Content").<br>
          You retain ownership of your content, but you grant us a non-exclusive, worldwide, royalty-free license to:
          <ul>
            <li>• Store.</li>
            <li>• Process.</li>
            <li>• Display.</li>
          </ul>
          This is solely for operating and improving the Service.<br>
          Your use of the Service is also governed by our Privacy Policy. We collect and process personal data as necessary to provide the Service.
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
        >Messaging and Communication</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          The Service includes a messaging feature. You acknowledge that:
          <ul>
            <li>• Messages are private between users but may be processed by our systems.</li>
            <li>• We may monitor or review messages to enforce these Terms or comply with legal obligations.</li>
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
        >Termination</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          We may suspend or terminate your access at any time, without prior notice, if you violate these Terms.
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
        >Disclaimer of Warranties</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          The Service is provided "as is" and "as available" without warranties of any kind.
        </p>
      </div>
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
        >Limitation of Liability</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          To the maximum extent permitted by law, we are not liable for:
          <ul>
            <li>• Any indirect or consequential damages.</li>
            <li>• Loss of data, profits, or business opportunities.</li>
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
        >Changes to Terms</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          We may update these Terms at any time. Continued use of the Service constitutes acceptance of the updated Terms.
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
        >Governing Law</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          These Terms are governed by the laws of Switzerland.
        </p>
      </div>
    </div>
    <SingleConnector color="suite42Blue" :height="2" />
    <div class="flex flex-row">
      <EndConnector color="suite42Blue" :height="textConnector" />
      <div class="flex flex-col w-full">
        <h4
          class="font-semibold font-h4-mobile
             md:font-h4-tablet
             lg:font-h4-laptop
             xl:font-h4-desktop"
          :style="{ color: colors.suite42Black }"
        >Contact</h4>
        <p
          class="font-regular font-body2-mobile
             md:font-body2-tablet
             lg:font-body2-laptop lg:w-2/3
             xl:font-bodyw-desktop xl:w-1/2"
          :style="{ color: colors.suite42Black }"
        >
          info.suite42@gmail.com
        </p>
      </div>
    </div>
  </section>
</template>
