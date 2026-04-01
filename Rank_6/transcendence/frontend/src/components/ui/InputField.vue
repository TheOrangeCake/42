<script setup lang="ts">
  import { colors } from '@/styles/Colors.ts'

  const inputFieldProps = defineProps<{
    label?: string
    modelValue: string | number
    tooltip?: string
    type?: string
    placeholder?: string
    inputmode?: 'text' | 'none' | 'tel' | 'url' | 'email' | 'numeric' | 'decimal' | 'search' | undefined
    maxlength?: string
  }>()

  const emit = defineEmits<{
    (e: 'update:modelValue', value: string): void
  }>()
</script>

<template>
  <div class="relative w-full">
    <label
      v-if="label"
      class="flex flex-row items-center gap-2 absolute -top-3 left-5 px-3 font-regular font-body2-mobile
                md:font-body2-tablet
                lg:font-body2-laptop
                xl:font-body2-desktop"
      :style="{ backgroundColor: colors.suite42Background, color: colors.suite42Darkgrey }"
    >
      {{ inputFieldProps.label }}
      <div
        v-if="tooltip"
        class="relative group"
      >
        <span
          class="cursor-help rounded-full border w-6 h-6 flex items-center justify-center font-regular font-body2-mobile
                         md:font-body2-tablet
                         lg:font-body2-laptop
                         xl:font-body2-desktop"
          :style="{
            color: colors.suite42Darkgrey,
            borderColor: colors.suite42Darkgrey }"
        >?</span>
        <div
          class="absolute left-8 -top-1.25 z-50 hidden group-hover:block w-48 px-3 py-2 rounded shadow-md font-regular pointer-events-nonefont-regular font-body2-mobile
                         md:font-body2-tablet
                         lg:font-body2-laptop
                         xl:font-body2-desktop"
          :style="{
            backgroundColor: colors.suite42Black,
            color: colors.suite42White
          }"
        >
          {{ inputFieldProps.tooltip }}
        </div>
      </div>
    </label>
    <input
      class="w-full border border-(--border-color-default) rounded px-3 py-3 outline-none focus:border-(--border-color) font-regular font-h5-mobile max-w-md
        md:font-h5-tablet
        lg:font-h5-laptop
        xl:font-h5-desktop"
      :inputmode="inputFieldProps.inputmode"
      :maxlength="inputFieldProps.maxlength"
      :placeholder="inputFieldProps.placeholder"
      :style="{
        backgroundColor: colors.suite42Background,
        color: colors.suite42Black,
        '--border-color-default': colors.suite42Grey,
        '--border-color': colors.suite42Blue
      }"
      :type="inputFieldProps.type ?? 'text'"
      :value="inputFieldProps.modelValue"
      @input="emit('update:modelValue', ($event.target as HTMLInputElement).value)"
    >
  </div>
</template>
