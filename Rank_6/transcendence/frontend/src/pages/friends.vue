<script setup lang="ts">
  import { useRouter } from 'vue-router'
  import {
    acceptFriendRequest,
    declineFriendRequest,
    type FriendshipDto,
    getFriends,
    getPendingRequests,
    getSentRequests,
    removeFriend,
    searchUsers,
    sendFriendRequest,
    sendHeartbeat,
    type UserSearchResult,
  } from '@/api/friends'
  import { useViewports } from '@/composables/useViewports.ts'
  import { viewportValue } from '@/composables/viewportsValue.ts'
  import { colors } from '@/styles/Colors.ts'

  definePage({
    meta: {
      requiresAuth: true,
      layout: 'dashboard',
    },
  })

  const tab = ref<'friends' | 'pending' | 'sent'>('friends')
  const friends = ref<FriendshipDto[]>([])
  const pending = ref<FriendshipDto[]>([])
  const sent = ref<FriendshipDto[]>([])
  const router = useRouter()
  const viewPort = useViewports().currentViewport
  const isDesktop = computed(() => viewPort.value === 'desktop')

  const searchQuery = ref('')
  const searchResults = ref<UserSearchResult[]>([])
  let searchTimeout: ReturnType<typeof setTimeout> | null = null

  function onSearch () {
    if (searchTimeout) clearTimeout(searchTimeout)
    const query = searchQuery.value.trim()
    if (query.length < 2) {
      searchResults.value = []
      return
    }
    searchTimeout = setTimeout(async () => {
      searchResults.value = await searchUsers(query)
    }, 300)
  }

  async function onSearchNow () {
    if (searchTimeout) clearTimeout(searchTimeout)
    const query = searchQuery.value.trim()
    if (query.length < 2) {
      searchResults.value = []
      return
    }
    searchResults.value = await searchUsers(query)
  }

  async function sendRequest (userId: number) {
    await sendFriendRequest(userId)
    searchQuery.value = ''
    searchResults.value = []
    await loadAll()
  }

  async function loadAll () {
    try {
      const [f, p, s] = await Promise.all([
        getFriends(),
        getPendingRequests(),
        getSentRequests(),
      ])
      friends.value = f
      pending.value = p
      sent.value = s
    } catch (error) {
      console.error('Failed to load friends data:', error)
    }
  }

  async function accept (id: number) {
    await acceptFriendRequest(id)
    await loadAll()
  }

  async function decline (id: number) {
    await declineFriendRequest(id)
    await loadAll()
  }

  async function remove (id: number) {
    await removeFriend(id)
    await loadAll()
  }

  function goToProfile (login: string) {
    router.push(`/user/${login}`)
  }

  let heartbeatInterval: ReturnType<typeof setInterval> | null = null

  onMounted(() => {
    loadAll()
    sendHeartbeat().catch(() => {})
    heartbeatInterval = setInterval(() => {
      sendHeartbeat().catch(() => {})
      loadAll()
    }, 30_000)
  })

  onUnmounted(() => {
    if (heartbeatInterval) clearInterval(heartbeatInterval)
  })

  const searchConnector = viewportValue({
    mobile: 1.5,
    tablet: 1.5,
    laptop: 1.6,
    desktop: 2,
  })
</script>

<template>
  <div
    class="flex flex-col w-full pl-4 pr-12 mb-20 mt-28
           md:mt-12
           lg:px-8 lg:mb-48
           xl:px-18
           2xl:px-28"
  >
    <h1
      class="font-bold font-h1-mobile
             md:font-h1-tablet
             lg:font-h1-laptop
             xl:font-h1-desktop"
      :style="{ color: colors.suite42Black }"
    >My buddies</h1>
    <SingleConnector color="suite42Blue" :height="3" />
    <div class="flex flex-col xl:flex-row xl:gap-20">
      <div class="flex flex-row">
        <EndConnector v-if="isDesktop" color="suite42Blue" :height="searchConnector" />
        <ConnectConnector v-else color1="suite42Blue" color2="suite42Green" :height="searchConnector" />
        <div
          class="flex flex-col w-full
                 md:w-auto"
        >
          <div class="flex flex-row gap-2">
            <InputField
              v-model="searchQuery"
              label="Search user"
              placeholder="user login"
              type="text"
              @input="onSearch"
              @keyup.enter="onSearchNow"
            />
            <SmallRedButton text="Search" @click="onSearchNow" />
          </div>
          <div v-if="searchResults.length > 0">
            <div
              v-for="u in searchResults"
              :key="u.id"
            >
              <FriendSearchCard text="Add friend" :user="u" @click="sendRequest(u.id)" />
            </div>
          </div>
          <div v-else-if="searchQuery && searchResults.length === 0">
            <p
              class="font-regular font-body1-mobile
                     md:font-body1-tablet
                     lg:font-body1-laptop
                     xl:font-body1-desktop"
            >No user with that name</p>
          </div>
        </div>
      </div>
      <SingleConnector v-if="!isDesktop" color="suite42Green" :height="4" />
      <div class="flex flex-row w-full max-w-2xl">
        <EndConnector v-if="!isDesktop" color="suite42Green" :height="searchConnector" />
        <div class="flex flex-col gap-8 w-full">
          <div class="flex flex-row gap-2 w-full">
            <TabSwitcher :active="tab === 'friends'" :count="friends.length" label="Friends" @click="tab = 'friends'" />
            <TabSwitcher :active="tab === 'pending'" :count="pending.length" label="Pending" @click="tab = 'pending'" />
            <TabSwitcher :active="tab === 'sent'" :count="sent.length" label="Sent" @click="tab = 'sent'" />
          </div>
          <div v-if="tab === 'friends'">
            <p
              v-if="friends.length === 0"
              class="font-regular font-body1-mobile
                     md:font-body1-tablet
                     lg:font-body1-laptop
                     xl:font-body1-desktop"
              :style="{ color: colors.suite42Black }"
            >No friends yet.</p>
            <div
              v-for="friend in friends"
              v-else
              :key="friend.id"
            >
              <FriendTabCard :friend="friend" type="friends" @button1="goToProfile(friend.friend_login)" @button2="remove(friend.id)" />
            </div>
          </div>
          <div v-if="tab === 'pending'">
            <p
              v-if="pending.length === 0"
              class="font-regular font-body1-mobile
                     md:font-body1-tablet
                     lg:font-body1-laptop
                     xl:font-body1-desktop"
              :style="{ color: colors.suite42Black }"
            >No pending request.</p>
            <div
              v-for="friend in pending"
              v-else
              :key="friend.id"
            >
              <FriendTabCard :friend="friend" type="pending" @button1="accept(friend.id)" @button2="decline(friend.id)" />
            </div>
          </div>
          <div v-if="tab === 'sent'">
            <p
              v-if="sent.length === 0"
              class="font-regular font-body1-mobile
                     md:font-body1-tablet
                     lg:font-body1-laptop
                     xl:font-body1-desktop"
              :style="{ color: colors.suite42Black }"
            >No request sent.</p>
            <div
              v-for="friend in sent"
              v-else
              :key="friend.id"
            >
              <FriendTabCard :friend="friend" type="sent" />
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
