<script setup lang="ts">
  import { computed, onMounted, ref } from 'vue'
  import { useRoute, useRouter } from 'vue-router'
  import { getUserProfile, type UserDetailed } from '@/api/api42.ts'
  import { getUserByLogin } from '@/api/api42.ts'
  import { ConflictError } from '@/api/errors.ts'
  import { sendFriendRequest } from '@/api/friends.ts'
  import { viewportValue } from '@/composables/viewportsValue.ts'
  import { useAuthStore } from '@/stores/auth.ts'
  import { colors } from '@/styles/Colors.ts'

  definePage({
    meta: {
      requiresAuth: true,
      layout: 'dashboard',
    },
  })

  const authStore = useAuthStore()
  const route = useRoute()
  const router = useRouter()
  const login = computed(() => (route.params as { login: string }).login)

  const profile = ref<UserDetailed | null>(null)
  const myProfile = ref<UserDetailed | null>(null)
  const isLoading = ref(false)
  const error = ref('')
  const friendRequestStatus = ref('')
  const isHovered = ref(false)

  const fullName = computed(() => {
    if (!profile.value) return ''
    return `${profile.value.first_name ?? ''} ${profile.value.last_name ?? ''}`.trim() || profile.value.login
  })

  function validUrl (url: string | null | undefined, fallback: string): string {
    if (!url || url.endsWith('/null')) return fallback
    return url
  }

  const avatarUrl = computed(() => {
    if (!profile.value) return '/design/assets/images/other_user_avatar_cropped.jpg'
    return validUrl(profile.value.custom_avatar_url, '')
      || validUrl(profile.value.image?.versions?.medium, '')
      || '/design/assets/images/other_user_avatar_cropped.jpg'
  })

  const bannerUrl = computed(() => {
    if (!profile.value) return '/design/assets/images/default_profile_banner.jpg'
    return validUrl(profile.value.custom_banner_url, '/design/assets/images/default_profile_banner.jpg')
  })

  const noBonusProjects = new Set([
    'exam-rank-02',
    'exam-rank-03',
    'exam-rank-04',
    'exam-rank-05',
    'exam-rank-06',
    'cpp-module-00',
    'cpp-module-01',
    'cpp-module-02',
    'cpp-module-03',
    'cpp-module-04',
    'cpp-module-05',
    'cpp-module-06',
    'cpp-module-07',
    'cpp-module-08',
    'cpp-module-09',
    'netpractice',
    '42_collaborative_resume',
  ])

  function scoreColor (m = 0, slug: string) {
    if (m >= 125) return { background: '#62D868', color: '#202020', bar: '#1D9E75' }
    if (m >= 100 && noBonusProjects.has(slug)) {
      return { background: '#62D868', color: '#202020', bar: '#1D9E75' }
    } else if (m >= 100)
      return { background: '#6AC8F8', color: '#202020', bar: '#6AC8F8' }
    if (m > 0) return { background: '#FF5959', color: '#202020', bar: '#FF5959' }
    return { background: '#FF5959', color: '#202020', bar: '#FF5959' }
  }

  function barWidth (mark: number | null, slug: string) {
    if (noBonusProjects.has(slug))
      return Math.round(Math.min(mark ?? 0, 100) / 100 * 100)
    return Math.round(Math.min(mark ?? 0, 125) / 125 * 100)
  }

  onMounted(async () => {
    if (authStore.isRegularUser) return
    try {
      myProfile.value = await getUserProfile()
    } catch (error_) {
      error.value = error_ instanceof Error ? error_.message : 'Failed to load profile'
      return
    }
    if (login.value === myProfile.value.login) {
      router.push('/profile')
    }
    isLoading.value = true
    try {
      profile.value = await getUserByLogin(login.value)
    } catch (error_) {
      error.value = error_ instanceof Error ? error_.message : 'User not found'
    } finally {
      isLoading.value = false
    }
  })

  async function sendRequest (userId: number) {
    try {
      await sendFriendRequest(userId)
      friendRequestStatus.value = 'Friend request sent !'
    } catch (error) {
      // friendRequestStatus.value = error === 'Conflict' ? 'Already friend or request already sent' : 'Fail to send request. Something went wrong'
      friendRequestStatus.value = error instanceof ConflictError ? 'Already friend or request already sent' : 'Failed to send request. Something went wrong'
      console.log('Fail to send friend request' + error)
    }
  }

  const connectorHeight1 = viewportValue({
    mobile: 1.2,
    tablet: 1.3,
    laptop: 1.6,
    desktop: 2,
  })
  const connectorHeight2 = viewportValue({
    mobile: 0.8,
    tablet: 1,
    laptop: 1,
    desktop: 1,
  })
  const connectorHeight3 = viewportValue({
    mobile: 1.3,
    tablet: 1.5,
    laptop: 1.5,
    desktop: 1.7,
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
    <h5
      v-if="isLoading"
      class="font-regular text-center font-h5-mobile py-10
             md:font-h5-tablet
             lg:font-h5-laptop
             xl:font-h5-desktop"
      :style="{ color: colors.suite42Black }"
    >Loading...</h5>
    <p
      v-else-if="error"
      class="font-regular text-center font-h5-mobile py-10
             md:font-h5-tablet
             lg:font-h5-laptop
             xl:font-h5-desktop"
      :style="{ color: colors.suite42Red }"
    >{{ error }}</p>

    <div v-else-if="profile">
      <h1
        class="font-bold font-h1-mobile
             md:font-h1-tablet
             lg:font-h1-laptop
             xl:font-h1-desktop"
        :style="{ color: colors.suite42Black }"
      >Oh hey, it's me!</h1>
      <SingleConnector color="suite42Blue" :height="3" />
      <div class="flex flex-row w-full items-start relative">
        <ConnectConnector color1="suite42Blue" color2="suite42Green" :height="4" />
        <div
          class="aspect-square w-32
                 md:w-40
                 lg:w-44
                 2xl:w-52"
        >
          <img
            alt="user avatar"
            class="object-cover w-full h-full rounded"
            :src="avatarUrl"
          >
        </div>
        <div
          class="flex flex-col ml-2 gap-2 absolute top-0 bottom-0 left-42 right-0
                 md:left-54
                 lg:left-60
                 2xl:left-70"
        >
          <img alt="banner" class="object-cover rounded w-full flex-1 min-h-0" :src="bannerUrl">
          <div class="flex flex-col w-fit shrink-0">
            <a
              class="font-bold font-h4-mobile hover:underline
                     md:font-h4-tablet
                     lg:font-h4-laptop
                     xl:font-h4-desktop"
              :href="profile.intra_url"
              rel="noopener noreferrer"
              :style="{ color: colors.suite42Black }"
              target="_blank"
            >{{ fullName }}</a>
            <p
              class="font-regular font-body2-mobile
                     md:font-body2-tablet
                     lg:font-body2-laptop
                     xl:font-body2-desktop"
              :style="{ color: colors.suite42Darkgrey }"
            >{{ profile?.email }}</p>
          </div>
        </div>
      </div>
      <SingleConnector color="suite42Green" :height="3" />
      <div class="flex flex-row">
        <ConnectConnector color1="suite42Green" color2="suite42Red" :height="connectorHeight1" />
        <div
          class="flex flex-row flex-wrap gap-4
                 md:gap-8
                 lg:gap-12
                 xl:gap-20"
        >
          <div class="flex flex-col">
            <h3
              class="font-regular font-h3-mobile
                       md:font-h3-tablet
                       lg:font-h3-laptop
                       xl:font-h3-desktop"
              :style="{ color: colors.suite42Black }"
            >Personal</h3>
            <SingleConnector color="suite42Green" :height="1" />
            <div class="flex flex-row">
              <EndConnector color="suite42Green" :height="connectorHeight2" />
              <p
                class="font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
                :style="{ color: colors.suite42Black }"
              >Intra login: {{ profile.login ?? '–' }}</p>
            </div>
            <SingleConnector color="suite42Green" :height="0.5" />
            <div class="flex flex-row">
              <EndConnector color="suite42Green" :height="connectorHeight2" />
              <p
                class="font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
                :style="{ color: colors.suite42Black }"
              >Pool: {{ profile.pool_month ?? '?' }} {{ profile.pool_year ?? '?' }}</p>
            </div>
            <SingleConnector color="suite42Green" :height="0.5" />
            <div class="flex flex-row">
              <EndConnector color="suite42Green" :height="connectorHeight2" />
              <span
                class="font-regular font-body1-mobile
                     md:font-body1-tablet
                     lg:font-body1-laptop
                     xl:font-body1-desktop"
                :style="{ color: colors.suite42Black }"
              >42 profile:
                <a
                  class="underline"
                  :href="profile.intra_url"
                  :style="{
                    color: isHovered ? colors.suite42Blue : colors.suite42Black
                  }"
                  target="_blank"
                  @mouseleave="isHovered = false"
                  @mouseover="isHovered = true"
                >{{ profile.login ?? '–' }}</a></span>
            </div>
          </div>
          <div class="flex flex-col">
            <h3
              class="font-regular font-h3-mobile
                       md:font-h3-tablet
                       lg:font-h3-laptop
                       xl:font-h3-desktop"
              :style="{ color: colors.suite42Black }"
            >Common Core</h3>
            <SingleConnector color="suite42Red" :height="1" />
            <div class="flex flex-row">
              <EndConnector color="suite42Red" :height="connectorHeight2" />
              <p
                class="font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
                :style="{ color: colors.suite42Black }"
              >Rank: {{ profile.rank }}</p>
            </div>
            <SingleConnector color="suite42Red" :height="0.5" />
            <div class="flex flex-row">
              <EndConnector color="suite42Red" :height="connectorHeight2" />
              <p
                class="font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
                :style="{ color: colors.suite42Black }"
              >Current rank progress: {{ profile.rank_progress_percent }}%</p>
            </div>
            <SingleConnector color="suite42Red" :height="0.5" />
            <div class="flex flex-row">
              <EndConnector color="suite42Red" :height="connectorHeight2" />
              <p
                class="font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
                :style="{ color: colors.suite42Black }"
              >Performance score: {{ profile.performance_score }}
                {{ profile.performance_score <= 1 ? 'point' : 'points' }}</p>
            </div>
            <SingleConnector color="suite42Red" :height="0.5" />
            <div class="flex flex-row">
              <EndConnector color="suite42Red" :height="connectorHeight2" />
              <div class="flex flex-col">
                <p
                  class="font-regular font-body1-mobile
                         md:font-body1-tablet
                         lg:font-body1-laptop
                         xl:font-body1-desktop"
                  :style="{ color: colors.suite42Black }"
                >Eligible projects:</p>
                <div
                  v-for="project in profile.eligible_projects"
                  :key="project"
                  class="flex flex-row"
                >
                  <EndConnector color="suite42Red" :height="connectorHeight2" />
                  <span>{{ project }}</span>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
      <SingleConnector color="suite42Red" :height="5" />
      <div class="flex flex-row w-full">
        <ConnectConnector color1="suite42Red" color2="suite42Black" :height="connectorHeight1" />
        <div
          class="flex flex-row flex-wrap gap-4 w-full
                 md:gap-8
                 lg:gap-12
                 xl:gap-20"
        >
          <div class="flex flex-col w-full">
            <h3
              class="font-regular font-h3-mobile
                       md:font-h3-tablet
                       lg:font-h3-laptop
                       xl:font-h3-desktop"
              :style="{ color: colors.suite42Black }"
            >Finished projects</h3>
            <div v-if="profile?.common_core" class="mt-4">
              <div
                class="flex flex-col gap-2
                       md:flex-row md:flex-wrap"
              >
                <div
                  v-for="rankGroup in profile.common_core.rank"
                  :key="rankGroup.rank"
                  class="w-full rounded p-2.5
                         md:flex-1 md:min-w-52"
                  :style=" {
                    backgroundColor: colors.suite42Black
                  }"
                >
                  <div class="flex">
                    <p
                      class="font-regular text-center font-body1-mobile py-1
                             md:font-body1-tablet
                             lg:font-body1-laptop
                             xl:font-body1-desktop"
                      :style="{
                        color: colors.suite42White
                      }"
                    >Rank {{ rankGroup.rank }}</p>
                  </div>
                  <div
                    v-for="project in rankGroup.projects.filter(p => (p.projects_users?.final_mark ?? 0) > 0)"
                    :key="project.slug"
                    class="border-1 rounded px-2.5 py-2 mb-1.5 last:mb-0"
                    :style="{
                      backgroundColor: colors.suite42Black,
                      borderColor: colors.suite42Darkgrey
                    }"
                  >
                    <div
                      class="font-semibold font-body2-mobile py-1
                             md:font-body2-tablet
                             lg:font-body2-laptop
                             xl:font-body2-desktop"
                      :style="{
                        color: colors.suite42Grey
                      }"
                    >
                      {{ project.name }}
                      <span
                        v-if="(project.projects_users?.occurrence ?? 0) > 0"
                        class="font-regular font-body2-mobile
                               md:font-body2-tablet
                               lg:font-body2-laptop
                               xl:font-body2-desktop"
                        :style="{ color: colors.suite42Darkgrey}"
                      > ({{ project.projects_users?.occurrence }} retries)</span>
                    </div>
                    <div class="flex flex-row items-center gap-2">
                      <div
                        class="flex-1 h-1 rounded"
                        :style="{ backgroundColor: colors.suite42Grey}"
                      >
                        <div
                          class="h-full rounded"
                          :style="{
                            width: barWidth(project.projects_users?.final_mark ?? 0, project.slug) + '%',
                            background: scoreColor(project.projects_users?.final_mark ?? 0, project.slug).bar
                          }"
                        />
                      </div>
                      <span
                        class="px-1.5 py-0.5 rounded font-regular font-body2-mobile
                               md:font-body2-tablet
                               lg:font-body2-laptop
                               xl:font-body2-desktop"
                        :style="scoreColor(project.projects_users?.final_mark ?? 0, project.slug)"
                      >{{ project.projects_users?.final_mark ?? 0 }}</span>

                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
      <SingleConnector color="suite42Black" :height="6" />
      <div class="flex flex-row">
        <EndConnector color="suite42Black" :height="connectorHeight3" />
        <div class="flex flex-col gap-4 items-start">
          <SmallRedButton text="Add friend" @click="sendRequest(profile.id)" />
          <span
            v-if="friendRequestStatus"
            class="font-regular font-body2-mobile
                   md:font-body2-tablet
                   lg:font-body2-laptop
                   xl:font-body2-desktop"
            :style="{ color: friendRequestStatus === 'Friend request sent !' ? colors.suite42Green : colors.suite42Red }"
          >{{ friendRequestStatus }}</span>
        </div>
      </div>
    </div>
    <div class="flex grow justify-end">
      <img alt="" class="w-75 md:w-100 lg:w-120 lg:h-120 xl:w-150 xl:h-150" src="/design/assets/images/other_user_page_illustration.png">
    </div>
  </div>
</template>
