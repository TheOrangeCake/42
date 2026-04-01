/**
 * main.ts
 *
 * Bootstraps Vuetify and other plugins then mounts the App`
 */

// Composables
import { createApp } from 'vue'
// Plugins
import { registerPlugins } from '@/plugins'

// Components
import App from './App.vue'

// Styles
import 'tailwindcss'
import 'unfonts.css'
import '@/styles/tailwind.css'
import '@/styles/themes.css'

const app = createApp(App)

registerPlugins(app)

app.mount('#app')
