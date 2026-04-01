<script setup lang="ts">
  import type { UserDetailed } from '@/api/api42.ts'
  import { computed, onMounted, ref } from 'vue'
  import { useRouter } from 'vue-router'
  import { getUserProfile } from '@/api/api42'
  import { useViewports } from '@/composables/useViewports'
  import { useAuthStore } from '@/stores/auth'
  import { colors } from '@/styles/Colors.ts'

  const authStore = useAuthStore()
  const router = useRouter()
  const viewPort = useViewports().currentViewport
  const isMobile = computed(() => viewPort.value === 'mobile')
  const isMobileMenuOpen = ref(false)
  const isHovered = ref(false)

  async function handleLogout () {
    await authStore.logout()
    router.push('/login')
  }

  onMounted(async () => {
    if (authStore.isRegularUser) return
    try {
      profile.value = await getUserProfile()
    } catch {
      profile.value = null
    }
  })
  const profile = ref<UserDetailed | null>(null)
  function validUrl (url: string | null | undefined, fallback: string): string {
    if (!url || url.endsWith('/null')) return fallback
    return url
  }
  const avatarUrl = computed(() => {
    if (authStore.isRegularUser) {
      return validUrl(authStore.user?.custom_avatar_url, '/design/assets/images/default_avatar_cropped.jpg')
    }
    if (!profile.value) return '/design/assets/images/default_avatar_cropped.jpg'
    return validUrl(profile.value.custom_avatar_url, '')
      || validUrl(profile.value.image?.versions?.medium, '')
      || '/design/assets/images/default_avatar_cropped.jpg'
  })

  const panelStyle = computed(() => ({
    backgroundColor: colors.suite42Black,
    transform: isMobileMenuOpen.value ? 'translateY(0)' : 'translateY(-100%)',
    opacity: isMobileMenuOpen.value ? 1 : 0,
    transition: 'transform 0.35s ease, opacity 0.25s ease',
  }))

  function canShowLink (user: string) {
    if (user === 'all') return true
    if (user === 'user42' && profile.value) return true
    return user === 'regular' && authStore.isRegularUser
  }

  function groupHasVisibleLinks (group: typeof navLinkGroups.value[0]) {
    return group.navLinks.some(link => canShowLink(link.user))
  }

  const navLinkGroups = computed(() => [
    {
      id: 1,
      navLinks: [
        { id: 1, label: 'Profile', link: '/profile', icon: avatarUrl.value, alt: '', isAvatar: true, user: 'all' },
      ],
    },
    {
      id: 2,
      navLinks: [
        { id: 1, label: 'Finder', link: '/finder', icon: '/design/assets/icons/finder.png', alt: '', isAvatar: false, user: 'user42' },
        // { id: 2, label: 'Projects', link: '/projects', icon: '/design/assets/icons/project.png', alt: '', isAvatar: false, user: 'user42' },
        // { id: 3, label: 'Tasks', link: '/tasks', icon: '/design/assets/icons/to-do-list.png', alt: '', isAvatar: false, user: 'user42' },
      ],
    },
    {
      id: 3,
      navLinks: [
        { id: 1, label: 'Home', link: '/home', icon: '/design/assets/icons/home.png', alt: '', isAvatar: false, user: 'all' },
        { id: 2, label: 'Chat', link: '/chat', icon: '/design/assets/icons/chat.png', alt: '', isAvatar: false, user: 'user42' },
        { id: 3, label: 'Friends', link: '/friends', icon: '/design/assets/icons/group.png', alt: '', isAvatar: false, user: 'user42' },
      ],
    },
  ])
</script>

<template>
  <div class="flex min-h-screen">
    <div
      v-if="isMobile"
      class="fixed top-0 left-0 flex flex-row w-full justify-between z-50 px-4 items-center shadow-sm"
      :style="{
        backgroundColor: isMobileMenuOpen ? colors.suite42Black : colors.suite42Background
      }"
    >
      <RouterLink class="" to="/">
        <img alt="Suite 42 logo" class="w-20 h-20 object-contain" src="/design/assets/logo/logo_icon.svg">
      </RouterLink>
      <div
        class="flex flex-col gap-1 p-4 rounded cursor-pointer"
        :style="{ backgroundColor: colors.suite42Black }"
        @click="isMobileMenuOpen = !isMobileMenuOpen"
      >
        <span
          class="w-5 h-0.5 transition-transform duration-300"
          :style="{
            transform: isMobileMenuOpen ? 'rotate(45deg) translateY(8.5px)' : 'rotate(0) translateY(0)',
            backgroundColor: colors.suite42White
          }"
        />
        <span
          class="w-5 h-0.5 transition-opacity duration-300"
          :style="{
            opacity: isMobileMenuOpen ? 0 : 1,
            backgroundColor: colors.suite42White
          }"
        />
        <span
          class="w-5 h-0.5 transition-transform duration-300"
          :style="{
            transform: isMobileMenuOpen ? 'rotate(-45deg) translateY(-8.5px)' : 'rotate(0) translateY(0)',
            backgroundColor: colors.suite42White
          }"
        />
      </div>
    </div>
    <div
      v-show="isMobile"
      class="fixed top-0 left-0 w-full h-screen z-40 overflow-hidden flex flex-col pt-32 px-12"
      :class="{ 'pointer-events-none': !isMobileMenuOpen }"
      :style="panelStyle"
    >
      <nav class="flex flex-col w-full items-end gap-12">
        <div
          v-for="(group, gIndex) in navLinkGroups"
          :key="group.id"
          class="flex flex-row gap-6"
        >
          <div
            v-for="(navLink, nIndex) in group.navLinks.filter(link => canShowLink(link.user))"
            :key="navLink.id"
            class="w-20"
            :style="{
              transition: 'transform 0.3s ease, opacity 0.3s ease',
              transitionDelay: `${(gIndex * group.navLinks.length + nIndex) * 0.05}s`,
              transform: isMobileMenuOpen ? 'translateY(0)' : 'translateY(-20px)',
              opacity: isMobileMenuOpen ? 1 : 0
            }"
          >
            <IntraNavLink
              :alt="navLink.alt"
              :icon="navLink.icon"
              :is-avatar="navLink.isAvatar"
              :label="navLink.label"
              :link="navLink.link"
              @click="isMobileMenuOpen = !isMobileMenuOpen"
            />
          </div>
        </div>
      </nav>
      <div class="border-t-1 my-12" :style="{ borderColor: colors.suite42Darkgrey }" />
      <div class="flex flex-row justify-end">
        <button
          class="font-regular font-body2-mobile border-1 rounded px-2 py-2 transition-colors duration-200"
          :style="{
            borderColor: isHovered ? colors.suite42Darkgrey : colors.suite42Black,
            color: isHovered ? colors.suite42White : colors.suite42Grey,
          }"
          @click="handleLogout"
          @mouseleave="isHovered = false"
          @mouseover="isHovered = true"
        >
          Sign out
        </button>
      </div>
    </div>

    <aside
      v-if="!isMobile"
      class="flex flex-col items-center py-6 px-1 fixed top-0 left-0 h-screen"
      :style="{
        backgroundColor: colors.suite42Black
      }"
    >
      <RouterLink class="mb-4" to="/">
        <img alt="Suite 42 logo" class="w-11 h-11 object-contain" src="/design/assets/logo/logo_icon.svg">
      </RouterLink>
      <nav
        class="flex flex-col "
      >
        <div
          v-for="group in navLinkGroups"
          :key="group.id"
          class="flex flex-col"
        >
          <div
            v-for="navLink in group.navLinks.filter(link => canShowLink(link.user))"
            :key="navLink.id"
          >
            <IntraNavLink
              :alt="navLink.alt"
              :icon="navLink.icon"
              :is-avatar="navLink.isAvatar"
              :label="navLink.label"
              :link="navLink.link"
            />
          </div>
          <div v-if="groupHasVisibleLinks(group)" class="border-t-1 my-4 mx-4" :style="{ borderColor: colors.suite42Darkgrey }" />
        </div>
      </nav>
      <button
        class="font-regular w-full mt-4 font-body2-mobile border-1 rounded px-2 py-2 transition-colors duration-200
                     md:font-body2-tablet
                     lg:font-body2-laptop
                     xl:font-body2-desktop"
        :style="{
          borderColor: isHovered ? colors.suite42Darkgrey : colors.suite42Black,
          color: isHovered ? colors.suite42White : colors.suite42Grey,
        }"
        @click="handleLogout"
        @mouseleave="isHovered = false"
        @mouseover="isHovered = true"
      >
        <span class="">Logout</span>
      </button>
    </aside>

    <main
      class="ml-0 flex-1 min-h-screen
            md:ml-24"
    >
      <router-view />
    </main>
  </div>
</template>
