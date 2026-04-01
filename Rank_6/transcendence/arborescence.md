# Titre 1

my-project/</br>
├─ public/                  # Fichiers statiques (favicon, images)</br>
├─ src/</br>
│  ├─ assets/               # Images, icônes, fichiers statiques importés</br>
│  ├─ components/           # Composants réutilisables</br>
│  │  └─ ui/                # Composants UI génériques (Button, Card, etc.)</br>
│  ├─ views/                # Pages ou vues (chaque route correspond à une vue)</br>
│  │  ├─ HomeView.vue</br>
│  │  ├─ AboutView.vue</br>
│  │  └─ DashboardView.vue</br>
│  ├─ layouts/              # Layouts (Header/Footer/Sidebar)</br>
│  ├─ router/               # Gestion des routes</br>
│  │  └─ index.ts</br>
│  ├─ store/                # Pinia / Vuex stores</br>
│  │  └─ index.ts</br>
│  ├─ composables/          # Fonctions réutilisables / hooks (useAuth, useFetch…)</br>
│  ├─ plugins/              # Plugins ou libs externes (Vuetify, Axios)</br>
│  ├─ types/                # Déclarations TypeScript globales ou interfaces</br>
│  ├─ styles/               # SCSS / CSS globaux</br>
│  │  └─ variables.scss</br>
│  ├─ App.vue               # Composant racine</br>
│  └─ main.ts               # Point d’entrée</br>
├─ package.json</br>
└─ vite.config.ts</br>