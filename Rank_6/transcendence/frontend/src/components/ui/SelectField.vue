<script setup lang="ts">
  import { colors } from '@/styles/Colors.ts'

  export type SelectOption = {
    id: number
    value: string
    text: string
  }

  const selectFieldProps = defineProps<{
    label: string
    modelValue: string
    options: SelectOption[]
    tooltip?: string
  }>()

  const emit = defineEmits<{
    (e: 'update:modelValue', value: string): void
  }>()
</script>

<template>
  <div class="relative w-full">
    <label
      class="flex flex-row items-center gap-2 absolute -top-3 left-5 px-3 font-regular font-body2-mobile
                md:font-body2-tablet
                lg:font-body2-laptop
                xl:font-body2-desktop"
      :style="{ backgroundColor: colors.suite42Background, color: colors.suite42Darkgrey }"
    >
      {{ selectFieldProps.label }}
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
          {{ selectFieldProps.tooltip }}
        </div>
      </div>
    </label>
    <select
      class="min-w-xs w-full border border-(--border-color-default) rounded px-3 py-3 outline-none focus:border-(--border-color) font-regular font-h5-mobile max-w-md
        md:font-h5-tablet
        lg:font-h5-laptop
        xl:font-h5-desktop"
      :style="{
        backgroundColor: colors.suite42Background,
        color: colors.suite42Black,
        '--border-color-default': colors.suite42Grey,
        '--border-color': colors.suite42Blue
      }"
      :value="selectFieldProps.modelValue"
      @change="emit('update:modelValue', ($event.target as HTMLSelectElement).value)"
    >
      <option
        v-for="option in selectFieldProps.options"
        :key="option.id"
        :value="option.value"
      >{{ option.text }}</option>
    </select>
  </div>
</template>
