<script setup lang="ts">
  import { useRouter } from 'vue-router'
  import { viewportValue } from '@/composables/viewportsValue'
  import { colors } from '@/styles/Colors.ts'

  const router = useRouter()
  const categories = [
    {
      id: 1,
      name: 'Front-end',
      color1: 'suite42Blue',
      color2: 'suite42Green',
      items: [
        'Vue.js',
        'Vuetify',
        'TailwindCSS',
        'Vite',
      ],
    },
    {
      id: 2,
      name: 'Design',
      color1: 'suite42Green',
      color2: 'suite42Red',
      items: [
        'Figma',
        'Adobe Illustrator',
      ],
    },
    {
      id: 3,
      name: 'Back-end',
      color1: 'suite42Red',
      color2: 'suite42Black',
      items: [
        'Java Spring Boot',
        'Java Spring Security',
        'Java JPA',
        'Hibernate ORM',
        'Nginx',
        'PostgreSQL',
        'Grafana',
        'Prometheus',
      ],
    },
    {
      id: 4,
      name: 'DevOps',
      color1: 'suite42Black',
      color2: 'suite42Blue',
      items: [
        'Docker / Docker Compose',
        'GitHub',
        'Java Spring Cloud Gateway',
        'HashiCorp Vault',
      ],
    },
  ]
  const techLogos = [
    { id: 1, name: 'Vue.js', src: '/design/assets/tech_logos/vuejs.png' },
    { id: 2, name: 'Tailwind CSS', src: '/design/assets/tech_logos/tailwindcss.svg' },
    { id: 3, name: 'Vite', src: '/design/assets/tech_logos/vite.svg' },
    { id: 4, name: 'Figma', src: '/design/assets/tech_logos/figma.svg' },
    { id: 5, name: 'Adobe Illustrator', src: '/design/assets/tech_logos/adobeIllustrator.svg' },
    { id: 6, name: 'Spring', src: '/design/assets/tech_logos/spring.svg' },
    { id: 7, name: 'Hibernate', src: '/design/assets/tech_logos/Hibernate.png' },
    { id: 8, name: 'Nginx', src: '/design/assets/tech_logos/nginx.svg' },
    { id: 9, name: 'PostgreSQL', src: '/design/assets/tech_logos/PostgreSQL.svg' },
    { id: 10, name: 'Grafana', src: '/design/assets/tech_logos/grafana.svg' },
    { id: 11, name: 'Prometheus', src: '/design/assets/tech_logos/Prometheus.svg' },
    { id: 12, name: 'Docker', src: '/design/assets/tech_logos/docker.svg' },
    { id: 13, name: 'GitHub', src: '/design/assets/tech_logos/github.svg' },
    { id: 14, name: 'HashiCorp Vault', src: '/design/assets/tech_logos/hashiCorp.svg' },
  ]

  const connectorHeight1 = viewportValue({
    mobile: 1.7,
    tablet: 2.1,
    laptop: 2.6,
    desktop: 3.6,
  })
  const connectorHeight2 = viewportValue({
    mobile: 0.8,
    tablet: 1,
    laptop: 1,
    desktop: 1,
  })
  const connectorHeight3 = viewportValue({
    mobile: 0.8,
    tablet: 1,
    laptop: 1,
    desktop: 1,
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
    <SingleConnector color="suite42Green" :height="6" />
    <div class="flex flex-row">
      <ConnectConnector color1="suite42Green" color2="suite42Red" :height="connectorHeight1" />
      <h1
        class="font-bold font-h1-mobile
               md:font-h1-tablet
               lg:font-h1-laptop
               xl:font-h1-desktop"
        :style="{ color: colors.suite42Black }"
      >Tech stack</h1>
    </div>
    <DoubleConnectors color1="suite42Red" color2="suite42Blue" :height="2" />
    <div
      class="flex flex-row gap-2
             md:gap-4"
    >
      <SingleConnector color="suite42Red" />
      <div
        class="flex flex-col gap-30
               xl:flex-row"
      >
        <div
          class="flex flex-col
                 xl:w-full"
        >
          <div
            v-for="category in categories"
            :key="category.id"
            class="flex flex-col"
          >
            <div class="flex flex-row">
              <ConnectConnector :color1="category.color1" :color2="category.color2" :height="connectorHeight2" />
              <div class="flex flex-col">
                <h5
                  class="font-bold font-h5-mobile
                       md:font-h5-tablet
                       lg:font-h5-laptop
                       xl:font-h5-desktop"
                  :style="{ color: colors.suite42Black }"
                >{{ category.name }}</h5>
                <div
                  v-for="item in category.items"
                  :key="item"
                  class="flex flex-row"
                >
                  <EndConnector :color="category.color1" :height="connectorHeight3" />
                  <span
                    class="font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
                    :style="{ color: colors.suite42Black }"
                  >{{ item }}</span>
                </div>
              </div>
            </div>
            <SingleConnector :color="category.color2" :height="2" />
          </div>
          <SingleConnector :color="'suite42Blue'" :height="4" />
          <div class="flex flex-row">
            <EndConnector :color="'suite42Blue'" :height="1.7" />
            <BigRedButton text="Let's start working !" @click="router.push('/login')" />
          </div>
        </div>
        <div class="flex flex-row gap-6 md:gap-10 flex-wrap justify-center">
          <div
            v-for="logo in techLogos"
            :key="logo.id"
            class="flex flex-col items-center justify-center w-24 h-24 md:w-32 m:h-32 p-2 rounded-lg shadow-sm transition duration-200 transform hover:scale-120 ease-out"
          >
            <img
              :alt="logo.name"
              class="h-12 md:h-16 w-auto object-contain mb-2"
              :src="logo.src"
            >
          </div>
        </div>
      </div>
    </div>
    <SingleConnector color="suite42Red" :height="12" />
  </section>
</template>
