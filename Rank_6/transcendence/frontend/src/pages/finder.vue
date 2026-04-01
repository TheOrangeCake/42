<script setup lang="ts">
  import type { SelectOption } from '@/components/ui/SelectField.vue'
  import { computed, onMounted, reactive, ref } from 'vue'
  import { useRouter } from 'vue-router'
  import { getUsers, type User42 } from '@/api/api42'
  import { useViewports } from '@/composables/useViewports.ts'
  import { viewportValue } from '@/composables/viewportsValue.ts'
  import { useAuthStore } from '@/stores/auth'
  import { colors } from '@/styles/Colors.ts'

  definePage({
    meta: { requiresAuth: true, layout: 'dashboard' },
  })

  const router = useRouter()
  const authStore = useAuthStore()
  const users = ref<User42[]>([])
  const isLoading = ref(false)
  const error = ref('')
  const totalElements = ref(0)
  const totalPages = ref(0)
  const panelOpen = ref(false)
  const viewPort = useViewports().currentViewport
  const isTablet = computed(() => viewPort.value === 'tablet')
  const isMobile = computed(() => viewPort.value === 'mobile')
  const isFirstPage = computed(() => filters.page === 0)
  const isLastPage = computed(() => filters.page >= totalPages.value - 1)

  const startYear = 2020
  const poolYears = computed(() => {
    const currentYear = new Date().getFullYear()

    return Array.from(
      { length: currentYear - startYear + 1 },
      (_, i) => (currentYear - i).toString(),
    )
  })

  // const commonProjects = ['ft_transcendence', 'webserv', 'cub3d', 'minirt', 'philosophers', 'cpp-module-09', 'ft_irc']
  const filters = reactive({
    campusName: 'Lausanne',
    page: 0,
    size: '25',
    rank: 'all',
    poolYear: 'all',
    poolMonth: 'all',
    eligibleProject: 'any',
    finishedProjects: [] as string[],
    minScore: 0,
    maxScore: 100,
    sort: 'performanceScore,desc',
    search: '',
  })

  function resetFilters () {
    filters.rank = 'all'
    filters.poolYear = 'all'
    filters.poolMonth = 'all'
    filters.eligibleProject = 'any'
    filters.finishedProjects = []
    filters.minScore = 0
    filters.maxScore = 100
    filters.sort = 'performanceScore,desc'
    filters.search = ''
    filters.page = 0
    filters.size = '25'
  }

  function closeFilters () {
    panelOpen.value = false
  }

  async function fetchUsers () {
    isLoading.value = true
    error.value = ''
    try {
      const res = await getUsers({
        ...filters,
      })
      users.value = res.content
      totalElements.value = res.page.totalElements
      totalPages.value = res.page.totalPages
    } catch (error_) {
      if (error_ instanceof Error) error.value = error_.message
    } finally {
      isLoading.value = false
    }
  }

  function validateScoreRange (min: number | undefined, max: number | undefined): string | null {
    const minVal = min === undefined || min === null || (min as unknown as string) === '' ? undefined : Number(min)
    const maxVal = max === undefined || max === null || (max as unknown as string) === '' ? undefined : Number(max)

    if (minVal == null && maxVal == null) return null
    if (minVal != null && !Number.isInteger(minVal)) {
      return 'Min score must be an integer'
    }
    if (maxVal != null && !Number.isInteger(maxVal)) {
      return 'Max score must be an integer'
    }
    if (minVal != null && (minVal < 0 || minVal > 100)) {
      return 'Min score must be between 0 and 100'
    }
    if (maxVal != null && (maxVal < 0 || maxVal > 100)) {
      return 'Max score must be between 0 and 100'
    }
    if (minVal != null && maxVal != null && minVal > maxVal) {
      return 'Min score cannot be greater than max score'
    }
    return null
  }

  function applyFilters () {
    const validationError = validateScoreRange(filters.minScore, filters.maxScore)
    if (validationError) {
      error.value = validationError
      filters.minScore = 0
      filters.maxScore = 100
      return
    }
    filters.page = 0
    panelOpen.value = false
    error.value = ''
    fetchUsers()
  }

  async function changePage (newPage: number) {
    filters.page = newPage
    await fetchUsers()
    window.scrollTo({ top: 0, behavior: 'smooth' })
  }

  function goToProfile (login: string) {
    router.push(`/user/${login}`)
  }

  onMounted(() => {
    if (authStore.isRegularUser) return
    fetchUsers()
  })

  const sortOptions: SelectOption[] = [
    { id: 1, value: 'performanceScore,desc', text: 'Performance ↓' },
    { id: 2, value: 'performanceScore,asc', text: 'Performance ↑' },
    { id: 3, value: 'rank,desc', text: 'Rank ↓' },
    { id: 4, value: 'rank,asc', text: 'Rank ↑' },
    { id: 5, value: 'poolYear,desc', text: 'Pool year ↓' },
    { id: 6, value: 'poolYear,asc', text: 'Pool year ↑' },
  ]

  const pageSizeOptions: SelectOption[] = [
    { id: 1, value: '10', text: '10' },
    { id: 2, value: '25', text: '25' },
    { id: 3, value: '50', text: '50' },
    { id: 4, value: '100', text: '100' },
  ]

  const rankOptions: SelectOption[] = [
    { id: 1, value: 'all', text: 'all' },
    { id: 2, value: '0', text: '0' },
    { id: 3, value: '1', text: '1' },
    { id: 4, value: '2', text: '2' },
    { id: 5, value: '3', text: '3' },
    { id: 6, value: '4', text: '4' },
    { id: 7, value: '5', text: '5' },
    { id: 8, value: '6', text: '6' },
  ]

  const poolMonthOptions: SelectOption[] = [
    { id: 1, value: 'all', text: 'all' },
    { id: 2, value: 'january', text: 'January' },
    { id: 3, value: 'february', text: 'February' },
    { id: 4, value: 'march', text: 'March' },
    { id: 5, value: 'april', text: 'April' },
    { id: 6, value: 'may', text: 'May' },
    { id: 7, value: 'june', text: 'June' },
    { id: 8, value: 'july', text: 'July' },
    { id: 9, value: 'august', text: 'August' },
    { id: 10, value: 'september', text: 'September' },
    { id: 11, value: 'october', text: 'October' },
    { id: 12, value: 'november', text: 'November' },
    { id: 13, value: 'december', text: 'December' },
  ]

  const poolYearOptions = computed<SelectOption[]>(() => [
    { id: 0, value: 'all', text: 'all' },
    ...poolYears.value.map((year, index) => ({
      id: index + 1,
      value: year,
      text: year,
    })),
  ])

  const projectOptions: SelectOption[] = [
    { id: 1, value: 'any', text: 'any' },
    { id: 2, value: '42cursus-libft', text: 'Libft' },
    { id: 3, value: '42cursus-get_next_line', text: 'Get next line' },
    { id: 4, value: '42cursus-ft_printf', text: 'Ft_printf' },
    { id: 5, value: 'born2beroot', text: 'Born2beroot' },
    { id: 6, value: '42cursus-push_swap', text: 'Push swap' },
    { id: 7, value: '42cursus-fdf', text: 'Fdf' },
    { id: 8, value: '42cursus-fract-ol', text: 'Fract-ol' },
    { id: 9, value: 'so_long', text: 'So long' },
    { id: 10, value: 'pipex', text: 'Pipex' },
    { id: 11, value: 'minitalk', text: 'Minitalk' },
    { id: 12, value: '42cursus-minishell', text: 'Minishell' },
    { id: 13, value: '42cursus-philosophers', text: 'Philosophers' },
    { id: 14, value: 'netpractice', text: 'Netpractice' },
    { id: 15, value: 'cpp-module-00', text: 'Cpp module 00' },
    { id: 16, value: 'cpp-module-01', text: 'Cpp module 01' },
    { id: 17, value: 'cpp-module-02', text: 'Cpp module 02' },
    { id: 18, value: 'cpp-module-03', text: 'Cpp module 03' },
    { id: 19, value: 'cpp-module-04', text: 'Cpp module 04' },
    { id: 20, value: 'minirt', text: 'Minirt' },
    { id: 21, value: 'cub3d', text: 'Cub3d' },
    { id: 22, value: 'inception', text: 'Inception' },
    { id: 23, value: 'cpp-module-05', text: 'Cpp module 05' },
    { id: 24, value: 'cpp-module-06', text: 'Cpp module 06' },
    { id: 25, value: 'cpp-module-07', text: 'Cpp module 07' },
    { id: 26, value: 'cpp-module-08', text: 'Cpp module 08' },
    { id: 27, value: 'cpp-module-09', text: 'Cpp module 09' },
    { id: 28, value: 'webserv', text: 'Webserv' },
    { id: 29, value: 'ft_irc', text: 'Ft_irc' },
    { id: 30, value: 'ft_transcendence', text: 'Ft_transcendence' },
    { id: 31, value: '42_collaborative_resume', text: 'Collaborative Resume' },
  ]

  const textConnector = viewportValue({
    mobile: 0.8,
    tablet: 1.1,
    laptop: 1,
    desktop: 1.1,
  })
  const filterConnector = viewportValue({
    mobile: 1.3,
    tablet: 1.4,
    laptop: 1.4,
    desktop: 1.5,
  })
  const filterMobileConnector = viewportValue({
    mobile: 1.5,
    tablet: 1.7,
    laptop: 0,
    desktop: 0,
  })
</script>

<template>
  <div
    class="flex flex-col w-full px-4 mb-32 mt-28
           md:mt-12
           lg:px-8 lg:mb-48
           xl:px-18
           2xl:px-28"
  >
    <div
      v-if="authStore.isRegularUser"
      class="flex flex-col text-center justtify-center"
    >
      <p
        class="font-bold font-h2-mobile leading-12
               md:font-h2-tablet md:leading-16
               lg:font-h2-laptop lg:leading-24
               xl:font-h2-desktop"
        :style="{ color: colors.suite42Black }"
      >42 students only</p>
      <p
        class="font-bold font-h5-mobile leading-12
               md:font-h5-tablet md:leading-16
               lg:font-h5-laptop lg:leading-24
               xl:font-h5-desktop"
        :style="{ color: colors.suite42Black }"
      >The Buddy Finder is only available for users connected with a 42 account.</p>
    </div>
    <div v-else>
      <h1
        class="font-bold font-h1-mobile leading-12
               md:font-h1-tablet md:leading-16
               lg:font-h1-laptop lg:leading-24
               xl:font-h1-desktop"
        :style="{ color: colors.suite42Black }"
      >Buddy finder</h1>
      <SingleConnector color="suite42Blue" :height="3" />
      <div class="flex flex-row">
        <ConnectConnector color1="suite42Blue" color2="suite42Green" :height="textConnector" />
        <p
          class="font-regular font-body1-mobile
               md:font-body1-tablet
               lg:font-body1-laptop
               xl:font-body1-desktop"
          :style="{ color: colors.suite42Black }"
        >Find a learning buddy or group members.
          <br>Result only contains active and non alumni students between rank 0 and 6.
          <br>Students that haven't finished <strong>42_Collaborative_resume</strong> but have already finished Common Core are still considered rank 6.</p>
      </div>
      <SingleConnector color="suite42Green" :height="3" />

      <div v-if="isTablet || isMobile">
        <div class="flex flex-row">
          <ConnectConnector color1="suite42Green" color2="suite42Red" :height="filterConnector" />
          <div class="flex flex-row gap-4 items-center">
            <FilterButton alt="" icon="design/assets/icons/filter_black.svg" text="Refine results" @click="panelOpen = !panelOpen" />
            <span
              class="font-regular font-body2-mobile
                 md:font-body2-tablet
                 lg:font-body2-laptop
                 xl:font-body2-desktop"
              :style="{ color: colors.suite42Darkgrey }"
            >{{ totalElements }} results</span>
          </div>
        </div>
        <div
          v-if="panelOpen"
          class="flex flex-row mt-2"
        >
          <Transition
            enter-active-class="transition-opacity duration-250 ease"
            enter-from-class="opacity-0"
            leave-active-class="transition-opacity duration-250 ease"
            leave-to-class="opacity-0"
          >
            <div
              v-if="panelOpen"
              class="fixed inset-0 z-40 opacity-60"
              :style="{
                backgroundColor: colors.suite42Black,
              }"
              @click="closeFilters"
            />
          </Transition>
          <Transition
            enter-active-class="transition-transform duration-300 ease"
            enter-from-class="translate-y-full"
            leave-active-class="transition-transform duration-300 ease"
            leave-to-class="translate-y-full"
          >
            <div
              v-if="panelOpen"
              class="fixed bottom-0 left-0 right-0 z-50 rounded-t-2xl overflow-y-auto max-h-[85dvh]"
              :style="{ backgroundColor: colors.suite42Background }"
            >
              <div class="flex justify-center pt-3 pb-2">
                <div
                  class="w-10 h-1 rounded-full"
                  :style="{ backgroundColor: colors.suite42Grey }"
                />
              </div>
              <div
                class="flex flex-row items-center justify-between px-6"
                :style="{ borderColor: colors.suite42Grey }"
              >
                <h4
                  class="font-semibold font-h4-mobile md:font-h4-tablet"
                  :style="{ color: colors.suite42Black }"
                >Refine results</h4>
                <button
                  class="w-8 h-8 flex items-center justify-center cursor-pointer"
                  :style="{ color: colors.suite42Darkgrey }"
                  @click="closeFilters"
                >✕</button>
              </div>
              <div class="flex flex-col px-6 pb-6">
                <SingleConnector color="suite42Green" :height="2" />
                <div class="flex flex-row">
                  <ConnectConnector color1="suite42Green" color2="suite42Blue" :height="filterMobileConnector" />
                  <InputField
                    v-model="filters.search"
                    label="Search"
                    placeholder="login"
                    tooltip="You can search by login, first name, or last name."
                    type="text"
                  />
                </div>
                <SingleConnector color="suite42Blue" :height="1" />
                <div class="flex flex-row">
                  <ConnectConnector color1="suite42Blue" color2="suite42Blue" :height="filterMobileConnector" />
                  <SelectField v-model="filters.rank" label="Rank" :options="rankOptions" />
                </div>
                <SingleConnector color="suite42Blue" :height="1" />
                <div class="flex flex-row">
                  <ConnectConnector color1="suite42Blue" color2="suite42Blue" :height="filterMobileConnector" />
                  <SelectField v-model="filters.poolMonth" label="Pool Month" :options="poolMonthOptions" />
                </div>
                <SingleConnector color="suite42Blue" :height="1" />
                <div class="flex flex-row">
                  <ConnectConnector color1="suite42Blue" color2="suite42Blue" :height="filterMobileConnector" />
                  <SelectField v-model="filters.poolYear" label="Pool Year" :options="poolYearOptions" />
                </div>
                <SingleConnector color="suite42Blue" :height="1" />
                <div class="flex flex-row">
                  <ConnectConnector color1="suite42Blue" color2="suite42Blue" :height="filterMobileConnector" />
                  <InputField v-model="filters.minScore" label="Min performance score" type="number" />
                </div>
                <SingleConnector color="suite42Blue" :height="1" />
                <div class="flex flex-row">
                  <ConnectConnector color1="suite42Blue" color2="suite42Blue" :height="filterMobileConnector" />
                  <InputField v-model="filters.maxScore" label="Max performance score" type="number" />
                </div>
                <SingleConnector color="suite42Blue" :height="1" />
                <div class="flex flex-row">
                  <ConnectConnector color1="suite42Blue" color2="suite42Blue" :height="filterMobileConnector" />
                  <SelectField v-model="filters.eligibleProject" label="Eligible project" :options="projectOptions" />
                </div>
                <SingleConnector color="suite42Blue" :height="1" />
                <div class="flex flex-row">
                  <ConnectConnector color1="suite42Blue" color2="suite42Red" :height="filterMobileConnector" />
                  <MultiSelectField v-model="filters.finishedProjects" label="Finished projects" :options="projectOptions" />
                </div>
                <SingleConnector color="suite42Red" :height="1" />
                <div class="flex flex-row">
                  <ConnectConnector color1="suite42Red" color2="suite42Red" :height="filterMobileConnector" />
                  <SelectField v-model="filters.sort" label="Sort" :options="sortOptions" />
                </div>
                <SingleConnector color="suite42Red" :height="1" />
                <div class="flex flex-row">
                  <EndConnector color="suite42Red" :height="filterMobileConnector" />
                  <SelectField v-model="filters.size" label="Result per page" :options="pageSizeOptions" />
                </div>
              </div>
              <div
                class="sticky bottom-0 flex flex-row gap-2 px-6 py-4 border-t"
                :style="{
                  backgroundColor: colors.suite42Background,
                  borderColor: colors.suite42Grey
                }"
              >
                <button
                  class="flex-1 py-3 rounded font-bold font-body1-mobile cursor-pointer transition-opacity hover:opacity-80
                         md:font-body1-tablet"
                  :style="{
                    backgroundColor: colors.suite42Blue,
                    color: colors.suite42Black
                  }"
                  @click="applyFilters"
                >Apply</button>
                <button
                  class="flex-1 py-3 rounded font-medium font-body1-mobile cursor-pointer transition-opacity hover:opacity-80
                         md:font-body1-tablet"
                  :style="{
                    backgroundColor: colors.suite42Darkgrey,
                    color: colors.suite42White
                  }"
                  @click="resetFilters"
                >Reset</button>
              </div>
            </div>
          </Transition>
        </div>
      </div>
      <div
        v-else-if="!isTablet && !isMobile"
        class="flex flex-row"
      >
        <ConnectConnector color1="suite42Green" color2="suite42Red" :height="filterConnector" />
        <div class="flex flex-col">
          <h4
            class="font-semibold font-h4-mobile
            md:font-h4-tablet
            lg:font-h4-laptop
            xl:font-h4-desktop"
            :style="{ color: colors.suite42Black }"
          >Refine result
            <span
              class="ml-2 font-regular font-body2-mobile
                 md:font-body2-tablet
                 lg:font-body2-laptop
                 xl:font-body2-desktop"
              :style="{ color: colors.suite42Darkgrey }"
            >{{ totalElements }} results</span>
          </h4>
          <div
            class="flex flex-col border-1 py-6 px-6 gap-6"
            :style="{
              borderColor: colors.suite42Grey
            }"
          >
            <div class="flex flex-row flex-wrap gap-6">
              <div class="flex flex-col gap-6">
                <InputField
                  v-model="filters.search"
                  label="Search"
                  placeholder="login"
                  tooltip="You can search by login, first name, or last name."
                  type="text"
                />
                <SelectField
                  v-model="filters.rank"
                  label="Rank"
                  :options="rankOptions"
                />
                <SelectField
                  v-model="filters.poolMonth"
                  label="Pool Month"
                  :options="poolMonthOptions"
                />
                <SelectField
                  v-model="filters.poolYear"
                  label="Pool Year"
                  :options="poolYearOptions"
                />
              </div>
              <div class="flex flex-col gap-6">
                <InputField
                  v-model="filters.minScore"
                  label="Min performance score"
                  type="number"
                />
                <InputField
                  v-model="filters.maxScore"
                  label="Max performance score"
                  type="number"
                />
              </div>
              <div class="flex flex-col gap-6">
                <SelectField
                  v-model="filters.eligibleProject"
                  label="Eligible project"
                  :options="projectOptions"
                />
                <MultiSelectField
                  v-model="filters.finishedProjects"
                  label="Finished projects"
                  :options="projectOptions"
                />
              </div>
              <div class="flex flex-col gap-6">
                <SelectField
                  v-model="filters.sort"
                  label="Sort"
                  :options="sortOptions"
                />
                <SelectField
                  v-model="filters.size"
                  label="Result per page"
                  :options="pageSizeOptions"
                />
              </div>
            </div>
            <div class="flex flex-row justify-end gap-2">
              <SmallRedButton text="Apply" @click="applyFilters" />
              <SmallBlueButton text="Reset" @click="resetFilters" />
            </div>
          </div>
        </div>
      </div>
    </div>
    <div
      v-if="isLoading"
      class="font-medium font-body1-mobile
             md:font-body1-tablet
             lg:font-body1-laptop
             xl:font-body1-desktop"
      :style="{ color: colors.suite42Black }"
    >Loading...</div>
    <p
      v-else-if="error"
      class="font-medium font-body1-mobile
             md:font-body1-tablet
             lg:font-body1-laptop
             xl:font-body1-desktop"
      :style="{ color: colors.suite42Red }"
    >{{ error }}</p>
    <div v-else>
      <SingleConnector color="suite42Red" :height="2" />
      <div v-if="users.length === 0">
        <p
          class="font-medium font-body1-mobile
             md:font-body1-tablet
             lg:font-body1-laptop
             xl:font-body1-desktop"
          :style="{ color: colors.suite42Darkgrey }"
        >No students found matching your filters</p>
      </div>
      <div
        v-else
        class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-2 2xl:grid-cols-3 gap-4 mb-20"
      >
        <FinderProfileCard
          v-for="user in users"
          :key="user.id"
          :user="user"
          @click="goToProfile(user.login)"
        />
      </div>
      <div
        v-if="totalPages > 1"
        class="flex flex-row gap-4 items-center justify-center"
      >
        <SmallBlueButton
          v-if="!isFirstPage"
          text="Previous"
          @click="changePage(filters.page - 1)"
        />
        <span
          class="font-regular font-body2-mobile
                 md:font-body2-tablet
                 lg:font-body2-laptop
                 xl:font-body2-desktop"
          :style="{ color: colors.suite42Black }"
        >{{ filters.page + 1 }} / {{ totalPages }}</span>
        <SmallBlueButton
          v-if="!isLastPage"
          text="Next"
          @click="changePage(filters.page + 1)"
        />
      </div>
    </div>
  </div>
</template>
