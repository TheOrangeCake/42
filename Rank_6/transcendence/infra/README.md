# Securite - WAF/ModSecurity + HashiCorp Vault

## C'est quoi ?

On a ajoute deux outils de securite :

- **Un pare-feu web (WAF)** qui bloque les attaques (injections SQL, XSS, etc.) avant qu'elles n'atteignent l'application
- **Un coffre-fort numerique (Vault)** qui stocke tous les mots de passe et cles secretes de maniere chiffree, au lieu de les laisser en clair dans un fichier .env

---

## Le WAF (ModSecurity)

### Comment ca marche ?

Avant, on avait un simple nginx qui faisait passer le trafic.
Maintenant, on utilise une version de nginx qui inclut **ModSecurity** : un module qui analyse chaque requete HTTP et bloque celles qui ressemblent a une attaque.

On utilise les **regles OWASP CRS** (Core Rule Set) : un ensemble de regles maintenues par la communaute securite, qui detectent les attaques les plus courantes.

### Ce qui est bloque

- Injections SQL (`' OR 1=1--`)
- Scripts XSS (`<script>alert(1)</script>`)
- Injections de commandes
- Traversees de repertoires (`../../etc/passwd`)
- Scanners automatiques

### Configuration

Le WAF est en **mode strict** (paranoia level 2) : il bloque les requetes suspectes.

Les WebSockets (pour le chat en temps reel) sont exemptes du WAF car le protocole n'est pas compatible avec ModSecurity.

### Pour tester

```bash
# Requete normale -> passe (200)
curl -ks https://localhost/

# Injection SQL -> bloquee (403)
curl -ks -o /dev/null -w "%{http_code}" "https://localhost/?id=1%27%20OR%201%3D1--"

# XSS -> bloquee (403)
curl -ks -o /dev/null -w "%{http_code}" "https://localhost/?q=%3Cscript%3Ealert(1)%3C/script%3E"
```

### Fichiers

- `modsecurity/REQUEST-900-EXCLUSION-RULES-BEFORE-CRS.conf` : exceptions pour eviter les faux positifs (OAuth, API JSON)
- `modsecurity/RESPONSE-999-EXCLUSION-RULES-AFTER-CRS.conf` : exceptions post-analyse (vide pour l'instant)

---

## Vault (gestion des secrets)

### Le probleme

Avant, tous les mots de passe etaient en clair dans le fichier `.env` : mots de passe des bases de donnees, cles JWT, credentials OAuth 42, etc.

### La solution

**HashiCorp Vault** est un coffre-fort qui :
- Stocke les secrets **chiffres sur disque**
- Donne a chaque service **uniquement les secrets dont il a besoin** (isolation)
- Permet de voir et gerer les secrets via une interface web

### Comment ca marche au demarrage

1. Le conteneur **Vault** demarre
2. Le conteneur **vault-init** s'execute :
   - Il initialise Vault (premiere fois uniquement)
   - Il deverrouille le coffre (unseal)
   - Il lit les secrets depuis le `.env` (fichier "seed") et les stocke dans Vault
   - Il genere un fichier `.env` par service avec uniquement ses secrets
3. Chaque service demarre et charge son fichier de secrets

### Isolation des secrets

Chaque service recoit uniquement ce dont il a besoin :

| Service | Secrets recus |
|---------|--------------|
| auth-service | mot de passe DB, credentials OAuth 42, cle JWT |
| chat-service | mot de passe DB, cle JWT |
| api42-service | mot de passe DB, credentials 42 (meme app que auth-service), cle JWT |
| regular-user-service | mot de passe DB, cle JWT, credentials email |
| postgres (x3) | uniquement son mot de passe |

### Les secrets persistent

Les secrets sont sauvegardes sur un volume Docker (`vault-data`).
Si on arrete et relance les conteneurs, les secrets sont toujours la.
Le script `vault-init` detecte que Vault est deja initialise et se contente de le deverrouiller.

### Acceder a l'interface Vault

1. Ouvrir `http://localhost:8200`
2. Choisir "Token" comme methode de connexion
3. Recuperer le token :
   ```bash
   docker exec vault cat /vault/file/vault-keys.json
   ```
4. Copier la valeur de `root_token` et la coller

### Fichiers

- `vault/config/vault.hcl` : configuration du serveur Vault
- `vault/scripts/init.sh` : script qui initialise et remplit le coffre

---

## Lancer le projet

```bash
cd infra
docker compose up -d
```

Tout demarre dans le bon ordre automatiquement.

Pour verifier que tout tourne :

```bash
docker compose ps
```
