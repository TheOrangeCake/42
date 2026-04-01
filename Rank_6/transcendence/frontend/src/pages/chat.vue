<script setup lang="ts">
  import { nextTick, onMounted, onUnmounted, ref, watch } from 'vue'
  import { getFriends, searchUsers, type UserSearchResult } from '@/api/friends'
  import { useAuthStore } from '@/stores/auth'
  import { colors } from '@/styles/Colors.ts'
  import {
    type ChatMessage,
    connectChat,
    disconnectChat,
    getMessageHistory,
    sendMessage,
  } from '../api/chat'

  definePage({
    meta: {
      requiresAuth: true,
      layout: 'dashboard',
    },
  })

  const STORAGE_KEY = 'chat_recent_contacts'

  const authStore = useAuthStore()
  const myId = authStore.user42?.login ?? authStore.user?.username ?? ''

  const recipientId = ref('')
  const searchInput = ref('')
  const messages = ref<ChatMessage[]>([])
  const inputText = ref('')
  const connected = ref(false)
  const recentContacts = ref<string[]>(JSON.parse(localStorage.getItem(STORAGE_KEY) ?? '[]'))
  const unreadContacts = ref<Set<string>>(new Set())
  const messagesEl = ref<HTMLElement | null>(null)

  const searchQuery = ref('')
  const searchResults = ref<UserSearchResult[]>([])
  let searchTimeout: ReturnType<typeof setTimeout> | null = null

  const showContacts = ref(true)
  const mobileShowContacts = ref(true)

  watch(recentContacts, val => {
    localStorage.setItem(STORAGE_KEY, JSON.stringify(val))
  }, { deep: true })

  function openConversation (login: string) {
    if (!login || login === myId) return
    searchInput.value = ''
    searchQuery.value = ''
    searchResults.value = []
    selectContact(login)
  }

  async function selectContact (login: string) {
    if (!recentContacts.value.includes(login)) {
      recentContacts.value.unshift(login)
    }
    mobileShowContacts.value = false
    unreadContacts.value.delete(login)
    recipientId.value = login
    messages.value = []

    try {
      messages.value = await getMessageHistory(myId, login)
      await scrollToBottom()
    } catch {
    // historique vide ou service indisponible
    }
  }

  function send () {
    const text = inputText.value.trim()
    if (!text || !recipientId.value) return

    const msg: ChatMessage = {
      senderId: myId,
      recipientId: recipientId.value,
      content: text,
      timestamp: Date.now(),
    }

    sendMessage(msg)
    messages.value.push(msg)
    inputText.value = ''
    scrollToBottom()
  }

  function formatTime (ts: number | string) {
    return new Date(ts as any).toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' })
  }

  async function scrollToBottom () {
    await nextTick()
    if (messagesEl.value) {
      messagesEl.value.scrollTop = messagesEl.value.scrollHeight
    }
  }

  onMounted(async () => {
    try {
      const friends = await getFriends()
      for (const f of friends) {
        if (f.status === 'ACCEPTED' && !recentContacts.value.includes(f.friend_login)) {
          recentContacts.value.push(f.friend_login)
        }
      }
    } catch {
    // service indisponible
    }
  })

  // Connexion WebSocket au montage
  connectChat(myId, msg => {
    const contact = msg.senderId === myId ? msg.recipientId : msg.senderId

    console.log('[CHAT] onMessage called')
    console.log('[CHAT] myId:', JSON.stringify(myId))
    console.log('[CHAT] recipientId.value:', JSON.stringify(recipientId.value))
    console.log('[CHAT] msg.senderId:', JSON.stringify(msg.senderId))
    console.log('[CHAT] msg.recipientId:', JSON.stringify(msg.recipientId))

    // Ajoute l'expéditeur aux contacts récents si pas déjà présent
    if (!recentContacts.value.includes(contact)) {
      recentContacts.value.unshift(contact)
    }

    // Si la conversation est ouverte, affiche le message directement
    const isActiveConv
      = (msg.senderId === recipientId.value && msg.recipientId === myId)
        || (msg.senderId === myId && msg.recipientId === recipientId.value)

    console.log('[CHAT] isActiveConv:', isActiveConv)

    if (isActiveConv) {
      messages.value.push(msg)
      scrollToBottom()
    } else {
      // Sinon marque le contact comme ayant un message non lu
      unreadContacts.value = new Set(unreadContacts.value).add(contact)
    }
  }, isConnected => {
    connected.value = isConnected
  })

  onUnmounted(() => {
    disconnectChat()
    connected.value = false
  })

  watch(recipientId, scrollToBottom)

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

</script>

<template>
  <div
    class="flex flex-col w-full mt-28 px-4 h-screen
           md:mt-12"
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
        class="font-bold font-h1-mobile
             md:font-h1-tablet md:leading-16
             lg:font-h1-laptop lg:leading-24
             xl:font-h1-desktop"
        :style="{ color: colors.suite42Black }"
      >Messages</h1>
      <div
        class="hidden lg:flex flex-row w-full border-1 rounded h-[70vh]"
        :style="{ borderColor: colors.suite42Grey }"
      >
        <div
          class="flex flex-col border-r-1 transition-all duration-300 overflow-hidden"
          :class="showContacts ? 'w-72 xl:w-1/3 2xl:w-96' : 'w-0'"
          :style="{ borderColor: colors.suite42Grey }"
        >
          <div
            class="flex flex-row items-centers gap-2 px-4 py-3 border-b-1 w-full"
            :style="{ borderColor: colors.suite42Grey }"
          >
            <div
              class="flex flex-row items-center py-3 border-b-1 w-full"
              :style="{ borderColor: colors.suite42Grey }"
            >
              <h3
                class="font-regular font-h3-mobile
                       lg:font-h3-laptop
                       xl:font-h3-desktop"
                :style="{ color: colors.suite42Black }"
              >Contacts</h3>
              <span
                class="w-4 h-4 rounded-full ml-auto mr-2 shrink-0"
                :style="{ backgroundColor: connected ? colors.suite42Green : colors.suite42Grey }"
                :title="connected ? 'Connected' : 'Disconnected'"
              />
              <button
                class="flex items-center border-l-1 justify-center w-8 h-full cursor-pointer font-bold font-h4-mobile lg:font-h4-laptop pl-8"
                :style="{
                  color: colors.suite42Black,
                  borderColor: colors.suite42Grey
                }"
                @click="showContacts = !showContacts"
              >←</button>
            </div>
          </div>
          <div
            class="flex flex-col w-full mb-2
                 md:w-auto"
          >
            <div class="relative">
              <InputField
                v-model="searchQuery"
                placeholder="user login"
                type="text"
                @input="onSearch"
                @keyup.enter="onSearchNow"
              />
              <div
                v-if="searchResults.length > 0"
                class="absolute w-full shadow-sm px-1 overflow-y-auto max-h-100"
                :style="{
                  backgroundColor: colors.suite42Background
                }"
              >
                <div
                  v-for="u in searchResults"
                  :key="u.id"
                >
                  <FriendSearchCard text="Chat" :user="u" @click="openConversation(u.login)" />
                </div>
              </div>
              <div
                v-else-if="searchQuery && searchResults.length === 0"
                class="absolute w-full shadow-sm px-1"
                :style="{
                  backgroundColor: colors.suite42Background
                }"
              >
                <p
                  class="font-regular font-body1-mobile
                     md:font-body1-tablet
                     lg:font-body1-laptop
                     xl:font-body1-desktop"
                >No user with that name</p>
              </div>
            </div>
          </div>
          <div class="flex flex-col overflow-y-auto">
            <div
              v-for="login in recentContacts"
              :key="login"
              class="flex flex-row items-center px-4 py-3 cursor-pointer transition-colors border-b-1"
              :style="{
                borderColor: colors.suite42Grey,
                backgroundColor: recipientId === login ? colors.suite42Blue + '22' : 'transparent',
              }"
              @click="selectContact(login)"
            >
              <div class="flex flex-row">
                <span
                  class="font-regular font-body1-mobile
                         lg:font-body1-laptop
                         xl:font-body1-desktop"
                  :style="{
                    color: unreadContacts.has(login) ? colors.suite42Blue : colors.suite42Black,
                    fontWeight: unreadContacts.has(login) ? '700' : '400',
                  }"
                >{{ login }}</span>
              </div>
              <span
                v-if="unreadContacts.has(login)"
                class="ml-auto w-2 h-2 rounded-full shrink-0"
                :style="{ backgroundColor: colors.suite42Blue }"
              />
            </div>
            <p
              v-if="recentContacts.length === 0"
              class="px-4 py-6 text-center font-regular font-body2-mobile
                     lg:font-body2-laptop"
              :style="{ color: colors.suite42Darkgrey }"
            >Enter a login to start a conversation.</p>
          </div>
        </div>
        <div
          class="flex flex-col flex-1 min-w-0"
          style="height: 70vh;"
        >
          <template v-if="recipientId">
            <div
              class="flex flex-row items-center gap-3 px-6 py-3 border-b-1 shrink-0"
              :style="{ borderColor: colors.suite42Grey }"
            >
              <div v-show="!showContacts">
                <button
                  class="flex items-center border-r-1 justify-center w-8 h-full cursor-pointer font-bold font-h4-mobile lg:font-h4-laptop pr-8"
                  :style="{
                    color: colors.suite42Black,
                    borderColor: colors.suite42Grey
                  }"
                  @click="showContacts = !showContacts"
                >→</button>
              </div>
              <h4
                class="font-regular font-h4-mobile
                       lg:font-h4-laptop
                       xl:font-h4-desktop"
                :style="{ color: colors.suite42Black }"
              >{{ recipientId }}</h4>
            </div>
            <div
              ref="messagesEl"
              class="flex flex-col gap-2 flex-1 overflow-y-auto px-6 py-4"
            >
              <div
                v-for="(msg, i) in messages"
                :key="i"
                class="flex flex-col"
                :class="msg.senderId === myId ? 'items-end' : 'items-start'"
              >
                <div
                  class="max-w-[60%] px-4 py-2 rounded-xl border-1 whitespace-pre-wrap wrap-anywhere"
                  :style="{
                    backgroundColor: colors.suite42Background,
                    color: colors.suite42Black,
                    borderColor: msg.senderId === myId ? colors.suite42Red : colors.suite42Blue,
                    borderBottomRightRadius: msg.senderId === myId ? '2px' : undefined,
                    borderBottomLeftRadius: msg.senderId !== myId ? '2px' : undefined,
                  }"
                >
                  <p
                    class="font-regular font-body1-mobile lg:font-body1-laptop"
                    :style="{ color: colors.suite42Black }"
                  >{{ msg.content }}</p>
                </div>
                <span
                  class="font-regular font-body2-mobile px-1"
                  :style="{ color: colors.suite42Darkgrey }"
                >{{ formatTime(msg.timestamp) }}</span>
              </div>
            </div>
            <div
              class="flex flex-row gap-3 px-6 py-3 border-t-1 shrink-0"
              :style="{ borderColor: colors.suite42Grey }"
            >
              <input
                v-model="inputText"
                autocomplete="off"
                class="flex-1 px-4 py-2 border-1 rounded font-regular font-body1-mobile lg:font-body1-laptop outline-none transition-colors"
                placeholder="Write a message..."
                :style="{
                  borderColor: colors.suite42Grey,
                  color: colors.suite42Black}"
                @keydown.enter="send"
              >
              <SmallRedButton
                :disabled="!inputText.trim()"
                text="Send"
                @click="send"
              />
            </div>
          </template>
          <div
            v-else
            class="flex flex-col w-full h-full"
          >
            <div
              v-show="!showContacts"
              class="px-4 py-3 border-b-1"
              :style="{ borderColor: colors.suite42Grey }"
            >
              <button
                class="cursor-pointer font-bold font-h4-mobile lg:font-h4-laptop"
                :style="{ color: colors.suite42Black }"
                @click="showContacts = !showContacts"
              >→</button>
            </div>
            <div class="flex flex-1 items-center justify-center">
              <p
                class="font-regular font-body1-mobile
             lg:font-body1-laptop
             xl:font-body1-desktop"
                :style="{ color: colors.suite42Darkgrey }"
              >Select a contact to start chatting.</p>
            </div>
          </div>
        </div>
      </div>

      <div class="flex lg:hidden flex-col w-full" style="height: 75dvh;">
        <div
          v-if="mobileShowContacts"
          class="flex flex-col w-full h-full border-1"
          :style="{ borderColor: colors.suite42Grey }"
        >
          <div
            class="flex flex-row items-center px-4 py-3 border-b-1 shrink-0"
            :style="{ borderColor: colors.suite42Grey }"
          >
            <h3
              class="font-semibold font-h4-mobile"
              :style="{ color: colors.suite42Black }"
            >Contacts</h3>
            <span
              class="w-4 h-4 rounded-full ml-auto shrink-0"
              :style="{ backgroundColor: connected ? colors.suite42Green : colors.suite42Grey }"
              :title="connected ? 'Connected' : 'Disconnected'"
            />
          </div>
          <div class="flex flex-col w-full">
            <div class="relative">
              <InputField
                v-model="searchQuery"
                placeholder="user login"
                type="text"
                @input="onSearch"
                @keyup.enter="onSearchNow"
              />
              <div
                v-if="searchResults.length > 0"
                class="absolute w-full shadow-sm px-1 overflow-y-auto max-h-60"
                :style="{ backgroundColor: colors.suite42Background }"
              >
                <div v-for="u in searchResults" :key="u.id">
                  <FriendSearchCard text="Chat" :user="u" @click="openConversation(u.login)" />
                </div>
              </div>
              <div
                v-else-if="searchQuery && searchResults.length === 0"
                class="absolute w-full shadow-sm px-1"
                :style="{ backgroundColor: colors.suite42Background }"
              >
                <p
                  class="font-regular font-body1-mobile"
                >No user with that name</p>
              </div>
            </div>
          </div>
          <div class="flex flex-col overflow-y-auto flex-1">
            <div
              v-for="login in recentContacts"
              :key="login"
              class="flex flex-row items-center px-4 py-3 cursor-pointer transition-colors border-b-1"
              :style="{
                borderColor: colors.suite42Grey,
                backgroundColor: recipientId === login ? colors.suite42Blue + '22' : 'transparent',
              }"
              @click="selectContact(login); mobileShowContacts = false"
            >
              <span
                class="font-regular font-body1-mobile"
                :style="{
                  color: unreadContacts.has(login) ? colors.suite42Blue : colors.suite42Black,
                  fontWeight: unreadContacts.has(login) ? '700' : '400',
                }"
              >{{ login }}</span>
              <span
                v-if="unreadContacts.has(login)"
                class="ml-auto w-2 h-2 rounded-full shrink-0"
                :style="{ backgroundColor: colors.suite42Blue }"
              />
            </div>
            <p
              v-if="recentContacts.length === 0"
              class="px-4 py-6 text-center font-regular font-body2-mobile"
              :style="{ color: colors.suite42Darkgrey }"
            >Enter a login to start a conversation.</p>
          </div>
        </div>
        <div
          v-else
          class="flex flex-col w-full h-full border-1"
          :style="{ borderColor: colors.suite42Grey }"
        >
          <div
            class="flex flex-row items-center gap-3 px-4 py-3 border-b-1 shrink-0"
            :style="{ borderColor: colors.suite42Grey }"
          >
            <button
              class="cursor-pointer font-bold font-h4-mobile shrink-0"
              :style="{ color: colors.suite42Black }"
              @click="mobileShowContacts = true"
            >←</button>
            <h3
              class="font-regular font-h3-mobile"
              :style="{ color: colors.suite42Black }"
            >{{ recipientId || '...' }}</h3>
          </div>
          <div
            ref="messagesEl"
            class="flex flex-col gap-2 flex-1 overflow-y-auto px-4 py-4"
          >
            <div
              v-for="(msg, i) in messages"
              :key="i"
              class="flex flex-col"
              :class="msg.senderId === myId ? 'items-end' : 'items-start'"
            >
              <div
                class="max-w-[75%] px-3 py-2 rounded-xl border-1 whitespace-pre-wrap wrap-anywhere"
                :style="{
                  backgroundColor: colors.suite42Background,
                  color: colors.suite42Black,
                  borderColor: msg.senderId === myId ? colors.suite42Red : colors.suite42Blue,
                  borderBottomRightRadius: msg.senderId === myId ? '2px' : undefined,
                  borderBottomLeftRadius: msg.senderId !== myId ? '2px' : undefined,
                }"
              >
                <p class="font-regular font-body1-mobile" :style="{ color: colors.suite42Black }">{{ msg.content }}</p>
              </div>
              <span
                class="font-regular font-body2-mobile px-1"
                :style="{ color: colors.suite42Darkgrey }"
              >{{ formatTime(msg.timestamp) }}</span>
            </div>
          </div>
          <div
            class="flex flex-row gap-2 px-4 py-3 border-t-1 shrink-0"
            :style="{ borderColor: colors.suite42Grey }"
          >
            <input
              v-model="inputText"
              autocomplete="off"
              class="flex-1 px-3 py-2 border-1 rounded font-regular font-body1-mobile outline-none"
              placeholder="Write a message..."
              :style="{ borderColor: colors.suite42Grey, color: colors.suite42Black }"
              @keydown.enter="send"
            >
            <SmallRedButton :disabled="!inputText.trim()" text="Send" @click="send" />
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
