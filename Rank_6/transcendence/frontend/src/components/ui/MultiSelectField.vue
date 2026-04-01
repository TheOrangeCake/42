<script setup lang="ts">
  import { computed, onBeforeUnmount, onMounted, ref } from 'vue'
  import { colors } from '@/styles/Colors.ts'

  export type SelectOption = { id: number, value: string, text: string }

  const selectFieldProps = defineProps<{
    label: string
    modelValue: string[]
    options: SelectOption[]
    tooltip?: string
  }>()

  const emit = defineEmits<{
    (e: 'update:modelValue', value: string[]): void
  }>()

  const search = ref('')
  const isOpen = ref(false)
  const dropdownRef = ref<HTMLElement | null>(null)

  const anyOption = selectFieldProps.options.find(option => option.value === 'any')
  const displayedOptions = computed(() => {
    if (selectFieldProps.modelValue.length === 0) {
      return anyOption ? [anyOption] : []
    }
    if (selectFieldProps.modelValue.includes('any')) {
      return anyOption ? [anyOption] : []
    }

    return selectFieldProps.options.filter(option =>
      selectFieldProps.modelValue.includes(option.value),
    )
  })

  const filteredOptions = computed(() =>
    selectFieldProps.options.filter(option =>
      option.text.toLowerCase().includes(search.value.toLowerCase())
      && !selectFieldProps.modelValue.includes(option.value),
    ),
  )

  function selectOption (option: SelectOption) {
    if (option.value === 'any') {
      emit('update:modelValue', ['any'])
    } else {
      const newValue = selectFieldProps.modelValue.filter(v => v !== 'any')
      emit('update:modelValue', [...newValue, option.value])
    }
    search.value = ''
    isOpen.value = false
  }

  function removeOption (value: string) {
    emit('update:modelValue', selectFieldProps.modelValue.filter(v => v !== value))
  }

  function handleClickOutside (event: MouseEvent) {
    if (dropdownRef.value && !dropdownRef.value.contains(event.target as Node)) {
      isOpen.value = false
    }
  }

  onMounted(() => document.addEventListener('click', handleClickOutside))
  onBeforeUnmount(() => document.removeEventListener('click', handleClickOutside))
</script>

<template>
  <div
    ref="dropdownRef"
    class="relative w-full"
  >
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
    <div
      class="w-full border border-(--border-color-default) rounded px-3 py-3 outline-none focus:border-(--border-color) font-regular font-h5-mobile max-w-md
        md:font-h5-tablet
        lg:font-h5-laptop
        xl:font-h5-desktop"
      :style="{
        backgroundColor: colors.suite42Background,
        color: colors.suite42Black,
        '--border-color-default': colors.suite42Grey,
        '--border-color': colors.suite42Blue
      }"
      @click="isOpen = true"
    >
      <span
        v-for="option in displayedOptions"
        :key="option.value"
        class="px-2 py-1 rounded flex items-center gap-1 font-h5-mobile
               md:font-h5-tablet
               lg:font-h5-laptop
               xl:font-h5-desktop"
        :style="{
          backgroundColor: colors.suite42Blue,
          color: colors.suite42Black }"
      >
        {{ option.text }}
        <button @click.stop="removeOption(option.value)">×</button>
      </span>
      <input
        v-model="search"
        class="flex-1 outline-none min-w-25"
        @focus="isOpen = true"
      >
      <div
        v-if="isOpen && filteredOptions.length > 0"
        class="absolute z-50 w-full mt-1 border rounded shadow max-h-60 overflow-y-auto"
        :style="{ backgroundColor: colors.suite42Background }"
      >
        <div
          v-for="option in filteredOptions"
          :key="option.id"
          class="px-3 py-2 cursor-pointer hover:bg-(--background-color)"
          :style="{
            '--background-color': colors.suite42Blue
          }"
          @click="selectOption(option)"
        >
          {{ option.text }}
        </div>
      </div>
    </div></div></template>
