# Transcendence

Projet full-stack en microservices : application web de gestion de projets 42 avec chat, profils, et authentification OAuth 42.

## Members:

- hoannguy: PO
- vgomes: Tech lead
- dconza: Dev
- alletond: PM
- dengelba: Dev

## Stack

| Couche | Techno |
|---|---|
| Frontend | Vue 3 + TypeScript + Vite + TailwindCSS |
| API Gateway | Spring Cloud Gateway |
| Backend | Spring Boot (microservices) |
| Auth | OAuth 42 + JWT + 2FA (OTP) |
| Base de données | PostgreSQL (une par service) |
| Secrets | HashiCorp Vault |
| WAF | OWASP ModSecurity (nginx) |
| Monitoring | Prometheus + Grafana |

---

## Prérequis

- Docker + Docker Compose
- `mkcert` (pour les certificats SSL locaux)
- Un compte 42 avec une **application OAuth créée sur l'intranet 42**

### Créer une application OAuth 42

1. Va sur [https://profile.intra.42.fr/oauth/applications](https://profile.intra.42.fr/oauth/applications)
2. Clique sur **"New Application"**
3. Remplis :
   - **Name** : ce que tu veux (ex: `transcendence-local`)
   - **Redirect URI** : `https://localhost/api/auth/callback/42`
   - **Scopes** : `public` minimum
4. Recupere le **Client ID** et le **Client Secret** -> ce sont tes `FORTYTWO_CLIENT_ID` et `FORTYTWO_CLIENT_SECRET`

---

## Installation

### 1. Cloner le repo

```bash
git clone <repo-url>
cd Transcendence
```

### 2. Configurer les variables d'environnement

Modifier les variables d'env du fichier .env.exemple a la racine du projet avec le clientid et le secret de l'application 42

### 3. Lancer le projet

```bash
make up
```

Le `make up` genere automatiquement les certificats SSL locaux via `mkcert` si absents, puis lance tous les containers.

Acces : **https://localhost**

> La premiere fois, le navigateur affichera un avertissement SSL (certificat auto-signe local). C'est normal, accepte l'exception.

---

## Commandes

```bash
make up          # Lancer (genere les certs SSL si besoin)
make down        # Arreter
make restart     # Rebuild complet + relancer
make logs        # Logs en direct
make ps          # Etat des containers
make clean       # Arreter + supprimer tous les volumes (reset complet)
```

---

## Architecture

```
https://localhost
       |
       v
    WAF (nginx + ModSecurity) :443
       |
       |-- /           -> frontend:3000     (Vue/Vite dev server)
       |-- /api/       -> api-gateway:8080  (routing general)
       |-- /api/chat/  -> chat-service:8082 (REST chat, bypass gateway)
       +-- /ws-chat/   -> chat-service:8082 (WebSocket STOMP)

api-gateway:8080
       |-- /api/auth/**             -> auth-service
       |-- /api/api42/**            -> api42-service
       |-- /api/regular-user/**     -> regular-user-service
       +-- /api/group/**            -> group-service
```

## Structure du repo

```
Transcendence/
|-- frontend/                   # Vue 3 + TypeScript
|-- backend/
|   |-- auth-service/           # OAuth 42 + JWT
|   |-- api42-service/          # Profils utilisateurs 42 (API intranet)
|   |-- regular-user-service/   # Comptes locaux (username/password) + 2FA OTP
|   |-- group-service/          # Groupes / systeme d'amis
|   +-- chat-service/           # Chat temps reel (WebSocket STOMP)
|-- api-gateway/                # Spring Cloud Gateway
+-- infra/
    |-- docker-compose.yml
    |-- nginx/nginx.conf         # Config WAF/reverse proxy
    |-- vault/                  # HashiCorp Vault (gestion des secrets)
    |-- prometheus/             # Config Prometheus
    +-- grafana/                # Dashboards Grafana
```

---

## Monitoring

| Service | URL |
|---|---|
| Prometheus | http://localhost:9090 |
| Grafana | http://localhost:3001 (login: admin / mdp: `GRAFANA_ADMIN_PASSWORD`) |


#**TL;DR**
1. Major: Use a framework for both the frontend and backend.
◦ Use a frontend framework.
◦ Use a backend framework.
◦ Full-stack frameworks (Next.js, Nuxt.js, SvelteKit) count as both if you use
both their frontend and backend capabilities.
2. Major: Implement real-time features using WebSockets or similar technology.
◦ Real-time updates across clients.
◦ Handle connection/disconnection gracefully.
◦ Efficient message broadcasting.
3. Major: Allow users to interact with other users. The minimum requirements are:
◦ A basic chat system (send/receive messages between users).
◦ A profile system (view user information).
◦ A friends system (add/remove friends, see friends list).
4. Minor: Use an ORM for the database.
5. Minor: Custom-made design system with reusable components, including a proper
color palette, typography, and icons (minimum: 10 reusable components).
6. Minor: Implement advanced search functionality with filters, sorting, and pagina-
tion.
7. Major: Standard user management and authentication.
◦ Users can update their profile information.
◦ Users can upload an avatar (with a default avatar if none provided).
◦ Users can add other users as friends and see their online status.
◦ Users have a profile page displaying their information.
8. Minor: Implement remote authentication with OAuth 2.0
9. Minor: Implement a complete 2FA system for the
users.
10. Major: Monitoring system with Prometheus and Grafana.
◦ Set up Prometheus to collect metrics.
◦ Configure exporters and integrations.
◦ Create custom Grafana dashboards.
◦ Set up alerting rules.
◦ Secure access to Grafana.
11. Major: Backend as microservices.
◦ Design loosely-coupled services with clear interfaces.
◦ Use REST APIs or message queues for communication.
◦ Each service should have a single responsibility.

Total de points:
6 Major + 5 Minor = 17
