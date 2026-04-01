<script setup lang="ts">
  import type { FriendshipDto } from '@/api/friends.ts'
  import { colors } from '@/styles/Colors.ts'

  defineProps<{
    friend: FriendshipDto
    type: 'friends' | 'pending' | 'sent'
  }>()

  const isRemoveHovered = ref(false)

  const emit = defineEmits(['button1', 'button2'])
</script>

<template>
  <div class="flex flex-row justify-between items-center my-2">
    <div class="flex flex-row gap-4 items-center">
      <div class="relative aspect-square rounded-full w-12 md:w-16">
        <img
          alt="user avatar"
          class="object-cover w-full h-full rounded-full"
          :src="friend.friend_avatar_url || '/design/assets/images/other_user_avatar_cropped.jpg'"
        >
        <span
          v-if="type === 'friends'"
          class="absolute border-1 -top-1 -right-1 w-5 aspect-square rounded-full"
          :style="{
            backgroundColor: friend.online ? colors.suite42Green : colors.suite42Grey,
            borderColor: colors.suite42Background
          }"
        />
      </div>
      <span
        class="font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
        :style="{ color: colors.suite42Black }"
      >{{ friend.friend_login }}</span>
    </div>
    <div v-if="type === 'friends'" class="flex flex-row gap-4 items-center">
      <SmallBlueButton text="View profile" @click="emit('button1')" />
      <button
        class="relative w-12 h-12 border-1 rounded transition-all"
        :style="{ borderColor: isRemoveHovered ? colors.suite42Red : colors.suite42Background }"
        @click="emit('button2')"
        @mouseleave="isRemoveHovered = false"
        @mouseover="isRemoveHovered = true"
      >
        <span class="absolute inset-0 flex items-center justify-center">
          <span
            class="block w-6 h-0.5 rotate-45"
            :style="{ backgroundColor: isRemoveHovered ? colors.suite42Red : colors.suite42Darkgrey }"
          />
          <span
            class="absolute block w-6 h-0.5 -rotate-45"
            :style="{ backgroundColor: isRemoveHovered ? colors.suite42Red : colors.suite42Darkgrey }"
          />
        </span>
      </button>
    </div>
    <div v-if="type === 'pending'" class="flex flex-row gap-4 items-center">
      <SmallBlueButton border-color="suite42Green" hover-text-color="suite42White" text="Accept" @click="emit('button1')" />
      <button
        class="relative w-12 h-12 border-1 rounded transition-all"
        :style="{ borderColor: isRemoveHovered ? colors.suite42Red : colors.suite42Background }"
        @click="emit('button2')"
        @mouseleave="isRemoveHovered = false"
        @mouseover="isRemoveHovered = true"
      >
        <span class="absolute inset-0 flex items-center justify-center">
          <span
            class="block w-6 h-0.5 rotate-45"
            :style="{ backgroundColor: isRemoveHovered ? colors.suite42Red : colors.suite42Darkgrey }"
          />
          <span
            class="absolute block w-6 h-0.5 -rotate-45"
            :style="{ backgroundColor: isRemoveHovered ? colors.suite42Red : colors.suite42Darkgrey }"
          />
        </span>
      </button>
    </div>
    <span
      v-if="type === 'sent'"
      class="font-regular font-boby1-mobile
             md:font-boby1-tablet
             lg:font-boby1-laptop
             xl:font-boby1-desktop"
      :style="{ color: colors.suite42Darkgrey }"
    >Pending...</span>
  </div>
</template>
