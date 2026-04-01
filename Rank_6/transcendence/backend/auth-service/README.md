# Auth Service - Service d'Authentification Transcendence

Service d'authentification basé sur OAuth2 (42 Intra) avec génération de JWT pour l'architecture microservices de Transcendence.

## 📋 Vue d'ensemble

Ce service gère :
- **Authentification OAuth2** via l'API 42
- **Génération de JWT** (JSON Web Tokens)
- **Validation des tokens** pour les autres microservices
- **Gestion de session** via cookies HTTP-only

## 🔐 Comment ça marche ?

### Flow d'authentification

1. **L'utilisateur initie la connexion** → Redirigé vers `/oauth2/authorization/42`
2. **OAuth2 avec 42** → L'utilisateur s'authentifie sur l'intra 42
3. **Callback** → 42 redirige vers `/login/oauth2/code/42`
4. **Génération JWT** → Le service génère un JWT signé contenant :
   - `sub` (subject) : login de l'utilisateur
   - `uid` : ID de l'utilisateur 42
   - `provider` : "42"
   - `email` : email de l'utilisateur
   - `iat` : timestamp de création
   - `exp` : timestamp d'expiration (2h par défaut)
5. **Cookie sécurisé** → Le JWT est stocké dans un cookie `access_token` (HttpOnly)
6. **Redirection** → L'utilisateur est redirigé vers le frontend

### Architecture JWT

Le JWT est signé avec **HMAC-SHA256** en utilisant le secret configuré dans `JWT_SECRET`.

**Structure du token :**
```json
{
  "sub": "login42",
  "uid": "12345",
  "provider": "42",
  "email": "user@student.42.fr",
  "iat": 1234567890,
  "exp": 1234575090
}
```

## 🚀 Utiliser l'authentification dans votre microservice

### Option 1 : Validation côté microservice (Recommandé)

Chaque microservice peut valider le JWT indépendamment sans appeler auth-service.

#### Étape 1 : Ajouter les dépendances (Maven)

```xml
<dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt-api</artifactId>
    <version>0.12.6</version>
</dependency>
<dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt-impl</artifactId>
    <version>0.12.6</version>
    <scope>runtime</scope>
</dependency>
<dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt-jackson</artifactId>
    <version>0.12.6</version>
    <scope>runtime</scope>
</dependency>
```

#### Étape 2 : Créer un filtre de validation JWT

```java
package com.example.yourservice.security;

import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.security.Keys;
import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;

import javax.crypto.SecretKey;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

@Component
public class JwtAuthenticationFilter extends OncePerRequestFilter {

    private final SecretKey key;
    private final String cookieName;

    public JwtAuthenticationFilter(
            @Value("${JWT_SECRET}") String secret,
            @Value("${app.jwt.cookie-name:access_token}") String cookieName) {
        this.key = Keys.hmacShaKeyFor(secret.getBytes(StandardCharsets.UTF_8));
        this.cookieName = cookieName;
    }

    @Override
    protected void doFilterInternal(HttpServletRequest request, 
                                  HttpServletResponse response, 
                                  FilterChain filterChain) 
            throws ServletException, IOException {
        
        String token = extractTokenFromCookie(request);
        
        if (token != null) {
            try {
                Claims claims = Jwts.parser()
                        .verifyWith(key)
                        .build()
                        .parseSignedClaims(token)
                        .getPayload();
                
                // Injecter les infos utilisateur dans la requête
                request.setAttribute("userLogin", claims.getSubject());
                request.setAttribute("userId", claims.get("uid"));
                request.setAttribute("userEmail", claims.get("email"));
                
            } catch (Exception e) {
                // Token invalide/expiré - continuer sans authentication
                response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                return;
            }
        }
        
        filterChain.doFilter(request, response);
    }

    private String extractTokenFromCookie(HttpServletRequest request) {
        Cookie[] cookies = request.getCookies();
        if (cookies != null) {
            for (Cookie cookie : cookies) {
                if (cookieName.equals(cookie.getName())) {
                    return cookie.getValue();
                }
            }
        }
        return null;
    }
}
```

#### Étape 3 : Configurer Spring Security

```java
package com.example.yourservice.config;

import com.example.yourservice.security.JwtAuthenticationFilter;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.security.web.authentication.UsernamePasswordAuthenticationFilter;

@Configuration
public class SecurityConfig {

    private final JwtAuthenticationFilter jwtAuthFilter;

    public SecurityConfig(JwtAuthenticationFilter jwtAuthFilter) {
        this.jwtAuthFilter = jwtAuthFilter;
    }

    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
            .csrf(csrf -> csrf.disable())
            .authorizeHttpRequests(auth -> auth
                .requestMatchers("/public/**", "/health").permitAll()
                .anyRequest().authenticated()
            )
            .addFilterBefore(jwtAuthFilter, UsernamePasswordAuthenticationFilter.class);
        
        return http.build();
    }
}
```

#### Étape 4 : Utiliser les infos utilisateur dans vos contrôleurs

```java
@RestController
@RequestMapping("/api/groups")
public class GroupController {

    @GetMapping("/my-groups")
    public ResponseEntity<?> getMyGroups(HttpServletRequest request) {
        String userLogin = (String) request.getAttribute("userLogin");
        String userId = (String) request.getAttribute("userId");
        
        if (userLogin == null) {
            return ResponseEntity.status(401).body("Not authenticated");
        }
        
        // Utiliser userLogin et userId pour récupérer les groupes
        return ResponseEntity.ok(/* ... */);
    }
}
```

### Option 2 : Appeler le endpoint /me

Si vous ne voulez pas gérer la validation JWT, vous pouvez appeler le endpoint `/me` du service auth.

```bash
curl -b "access_token=<JWT>" http://localhost:8080/api/auth/me
```

Réponse en cas de succès :
```json
{
  "authenticated": true,
  "sub": "login42",
  "email": "user@student.42.fr",
  "iat": "2024-01-01T10:00:00Z",
  "exp": "2024-01-01T12:00:00Z"
}
```

Réponse si non authentifié :
```json
{
  "authenticated": false
}
```

## ⚙️ Configuration

### Variables d'environnement requises

```bash
# Secret pour signer les JWT (minimum 32 caractères)
JWT_SECRET=votre-secret-ultra-securise-de-min-32-caracteres

# OAuth2 42
FORTYTWO_CLIENT_ID=votre-client-id
FORTYTWO_CLIENT_SECRET=votre-client-secret

# URL du frontend (pour la redirection post-login)
FRONTEND_BASE_URL=http://localhost:8080
```

### Configuration application.yml

```yaml
server:
  port: 8080
  servlet:
    context-path: /api/auth

app:
  jwt:
    secret: ${JWT_SECRET}
    cookie-name: access_token
    ttl-minutes: 120  # Durée de validité du token (2h)
  frontend:
    base-url: ${FRONTEND_BASE_URL:http://localhost:8080}
  allowed-campus-ids: [47]  # Campus autorisés (Nice = 47)

spring:
  security:
    oauth2:
      client:
        registration:
          42:
            client-id: ${FORTYTWO_CLIENT_ID}
            client-secret: ${FORTYTWO_CLIENT_SECRET}
            authorization-grant-type: authorization_code
            redirect-uri: "{baseUrl}/login/oauth2/code/{registrationId}"
            scope:
              - public
        provider:
          42:
            authorization-uri: https://api.intra.42.fr/oauth/authorize
            token-uri: https://api.intra.42.fr/oauth/token
            user-info-uri: https://api.intra.42.fr/v2/me
            user-name-attribute: login
```

## 🔧 Endpoints disponibles

| Méthode | Endpoint | Description | Auth requise |
|---------|----------|-------------|--------------|
| GET | `/oauth2/authorization/42` | Initier l'authentification OAuth2 | Non |
| GET | `/me` | Récupérer les infos de l'utilisateur connecté | Oui (cookie) |
| POST | `/logout` | Se déconnecter (supprime le cookie) | Non |
| GET | `/public/health` | Health check | Non |

## 🏃 Démarrage rapide

### En local

```bash
# 1. Configurer les variables d'environnement
export JWT_SECRET="mon-super-secret-de-minimum-32-caracteres-pour-securite"
export FORTYTWO_CLIENT_ID="votre-client-id"
export FORTYTWO_CLIENT_SECRET="votre-client-secret"
export FRONTEND_BASE_URL="http://localhost:8080"

# 2. Compiler et lancer
./mvnw clean package
java -jar target/auth-service-0.0.1-SNAPSHOT.jar
```

### Avec Docker

```bash
docker build -t auth-service .
docker run -p 8080:8080 \
  -e JWT_SECRET="mon-super-secret" \
  -e FORTYTWO_CLIENT_ID="..." \
  -e FORTYTWO_CLIENT_SECRET="..." \
  -e FRONTEND_BASE_URL="http://localhost:8080" \
  auth-service
```

## 🔒 Sécurité

- ✅ **JWT signé** avec HMAC-SHA256
- ✅ **Cookie HttpOnly** (protection XSS)
- ✅ **Expiration automatique** des tokens (2h)
- ✅ **Secret partagé** entre microservices pour validation décentralisée
- ⚠️ **Cookie Secure=false** en dev (à activer en production avec HTTPS)

## 📝 Notes importantes

1. **Le JWT_SECRET doit être identique** sur tous les microservices qui valident les tokens
2. **Minimum 32 caractères** pour le JWT_SECRET (recommandé : 64+)
3. **En production** : passer `cookie.setSecure(true)` dans `FortyTwoSuccessHandler`
4. **Campus autorisés** : configuré via `app.allowed-campus-ids` (actuellement Nice = 47)

## 🐛 Debug

Des endpoints de debug sont disponibles en développement :

- `GET /debug/env` : Variables d'environnement
- `GET /debug/jwt` : Test de génération/parsing de JWT
- `GET /debug/oauth2` : Configuration OAuth2

⚠️ **À supprimer en production !**

## 📦 Dépendances clés

- Spring Boot 3.3.4
- Spring Security OAuth2 Client
- JJWT 0.12.6 (JWT)
- Java 17

## 🤝 Contribuer

Pour ajouter des claims au JWT, modifier :
1. `FortyTwoSuccessHandler.java` : ajout des claims lors de la génération
2. `MeController.java` : exposition des nouveaux claims via `/me`

---

**Auteur** : Équipe Transcendence  
**Licence** : MIT
