<script setup lang="ts">
  import type { UserSearchResult } from '@/api/friends.ts'
  import { colors } from '@/styles/Colors.ts'

  defineProps<{
    user: UserSearchResult
    text: string
  }>()
  const emit = defineEmits(['click'])
</script>

<template>
  <div class="flex flex-row justify-between items-center my-2">
    <div class="flex flex-row gap-4 items-center">
      <div class="aspect-square rounded-full overflow-hidden w-16">
        <img
          alt="user avatar"
          class="object-cover w-full h-full"
          :src="user.avatar_url || '/design/assets/images/other_user_avatar_cropped.jpg'"
        >
      </div>
      <span
        class="font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
        :style="{ color: colors.suite42Black }"
      >{{ user.login }}</span>
    </div>
    <div class="flex flex-row gap-4">
      <SmallBlueButton :text="text" @click="emit('click')" />
    </div>
  </div>
</template>
