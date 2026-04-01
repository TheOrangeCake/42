export const colors = {
  suite42Red: '#FF5959',
  suite42Green: '#62D868',
  suite42Blue: '#6AC8F8',
  suite42Black: '#202020',
  suite42White: '#F8F8F8',
  suite42Grey: '#D9D9D9',
  suite42Darkgrey: '#5B5B5B',
  suite42Background: '#FFFFFF',
} as const

export type Colors = keyof typeof colors
