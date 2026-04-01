<script setup lang="ts">
  import { colors } from '@/styles/Colors.ts'

  const isHovered = ref(false)
  const uploadFieldProps = defineProps<{
    label: string
    buttonText: string
    file?: File | null
  }>()

  const emit = defineEmits(['change'])
</script>

<template>
  <div class="flex flex-col gap-1">
    <label
      class="font-regular font-body1-mobile
                     md:font-body1-tablet
                     lg:font-body1-laptop
                     xl:font-body1-desktop"
    >{{ uploadFieldProps.label }}</label>
    <div class="flex flex-row">
      <div
        class="flex items-center border-1 rounded overflow-hidden w-full max-w-sm
               lg:max-w-xl"
        :style="{
          borderColor: colors.suite42Darkgrey
        }"
      >
        <label
          class="flex px-4 h-full items-center border-r-1 cursor-pointer shrink-0 font-regular font-body2-mobile
                     md:font-body2-tablet
                     lg:font-body2-laptop
                     xl:font-body2-desktop"
          :style="{
            backgroundColor: isHovered ? colors.suite42Blue : colors.suite42White,
            borderColor: colors.suite42Grey
          }"
          @mouseleave="isHovered = false"
          @mouseover="isHovered = true"
        >
          {{ uploadFieldProps.buttonText }}
          <input
            accept=".png,.jpg,.jpeg,.gif,.webp,.svg"
            class="hidden"
            type="file"
            @change="(e) => emit('change', (e.target as HTMLInputElement).files?.[0])"
          >
        </label>
        <span
          class="flex-1 px-3 py-2 truncate font-regular font-body1-mobile
                       md:font-body1-tablet
                       lg:font-body1-laptop
                       xl:font-body1-desktop"
          :style="{
            color: uploadFieldProps.file?.name ? colors.suite42Darkgrey :colors.suite42Grey
          }"
        >{{ uploadFieldProps.file?.name ?? 'png, svg, jpg, webp, gif' }}</span>
      </div>
    </div>
  </div>

</template>
