# Tests du Auth Service

Ce répertoire contient une suite complète de tests unitaires et d'intégration pour le service d'authentification.

## Structure des tests

```
src/test/java/com/transcendence/auth/
├── AuthServiceApplicationTests.java      # Tests d'intégration
├── config/
│   └── AppSecurityPropertiesTest.java    # Tests de configuration
├── security/
│   ├── JwtServiceTest.java              # Tests unitaires du service JWT
│   └── FortyTwoSuccessHandlerTest.java   # Tests du handler OAuth2
└── web/
    └── MeControllerTest.java            # Tests du contrôleur /me
```

## Exécution des tests

### Tous les tests
```bash
mvn test
```

### Tests spécifiques
```bash
# Tests unitaires du service JWT
mvn test -Dtest=JwtServiceTest

# Tests d'intégration
mvn test -Dtest=AuthServiceApplicationTests

# Tests du contrôleur
mvn test -Dtest=MeControllerTest

# Tests du handler OAuth2
mvn test -Dtest=FortyTwoSuccessHandlerTest
```

### Avec rapport de couverture
```bash
mvn test jacoco:report
# Accédez à target/site/jacoco/index.html
```

### Watch mode (surveillance automatique)
```bash
mvn test -Dtest -DwatchMode=true
```

## Suites de tests

### 1. **JwtServiceTest** (11 tests)
Valide la génération et le parsing des tokens JWT:
- ✅ Création de tokens avec claims
- ✅ Parsing et validation des tokens
- ✅ Gestion des tokens invalides/expirés
- ✅ TTL customisable
- ✅ Claims vides autorisés

**Exécution:**
```bash
mvn test -Dtest=JwtServiceTest
```

### 2. **MeControllerTest** (8 tests)
Teste l'endpoint `/me`:
- ✅ Endpoint avec token valide → 200 + infos utilisateur
- ✅ Endpoint sans token → 401 + authenticated=false
- ✅ Endpoint avec token expiré → 401
- ✅ Endpoint avec token invalide → 401
- ✅ Structure complète de la réponse

**Exécution:**
```bash
mvn test -Dtest=MeControllerTest
```

### 3. **FortyTwoSuccessHandlerTest** (7 tests)
Teste la gestion de l'authentification OAuth2:
- ✅ Génération du JWT après login réussi
- ✅ Cookie HttpOnly configuré correctement
- ✅ Redirection vers le frontend
- ✅ Rejet si login est null/vide → 403
- ✅ Claims (provider, uid) ajoutés au token

**Exécution:**
```bash
mvn test -Dtest=FortyTwoSuccessHandlerTest
```

### 4. **AuthServiceApplicationTests** (11 tests)
Tests d'intégration avec Spring Boot:
- ✅ Démarrage de l'application
- ✅ Endpoints publics accessibles sans auth
- ✅ Endpoints protégés nécessitent un token
- ✅ Validation des claims du JWT
- ✅ Gestion des cookies

**Exécution:**
```bash
mvn test -Dtest=AuthServiceApplicationTests
```

### 5. **AppSecurityPropertiesTest** (5 tests)
Tests de configuration:
- ✅ Valeurs par défaut
- ✅ Setter/Getter pour les campus IDs
- ✅ Listes de campus

**Exécution:**
```bash
mvn test -Dtest=AppSecurityPropertiesTest
```

## Total: 42 tests ✅

## Environnements de test

Les tests utilisent:
- **JUnit 5** pour les tests unitaires
- **Mockito** pour les mocks et stubs
- **Spring Boot Test** pour les tests d'intégration
- **MockMvc** pour les tests HTTP

## Configuration pour les tests

Les tests utilisent des configurations mockées pour éviter les dépendances externes:

```yaml
# Application-test.yml (utilisé automatiquement par Spring Boot Test)
server:
  port: 0  # Port aléatoire pour les tests
  
app:
  jwt:
    secret: mon-super-secret-de-minimum-32-caracteres-pour-securite
    ttl-minutes: 120
  frontend:
    base-url: http://localhost:8080
  allowed-campus-ids: [47]
```

## Dépendances pour les tests

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
    <scope>test</scope>
</dependency>
```

## Résultats attendus

Après l'exécution de tous les tests:

```
Tests run: 42, Failures: 0, Errors: 0, Skipped: 0

BUILD SUCCESS
```

## Intégration CI/CD

Pour une utilisation dans CI/CD, exécutez:

```bash
# Build avec tests
mvn clean package

# Build sans tests
mvn clean package -DskipTests

# Tests uniquement avec rapports
mvn clean test jacoco:report
```

## Dépannage

### Tests qui échouent
1. Assurez-vous que `JWT_SECRET` a au moins 32 caractères
2. Vérifiez que Spring Boot est version 3.3.4+
3. Confirmez que tous les modules Maven sont compilés

### Erreurs de dépendances
```bash
mvn clean dependency:resolve
```

### Réinitialiser les caches
```bash
rm -rf ~/.m2/repository
mvn clean install
```

## Bonnes pratiques

✅ Exécutez les tests avant chaque commit
✅ Gardez la couverture > 80%
✅ Nommez les tests: `test[Scenario][Output]`
✅ Utilisez Arrange-Act-Assert
✅ Mockez les dépendances externes

## Contribution

Pour ajouter des tests:
1. Créez la classe `*Test` dans le bon paquet
2. Préfixez les méthodes de test par `test`
3. Utilisez `@Test` de JUnit 5
4. Suivez le pattern AAA (Arrange-Act-Assert)

Exemple:
```java
@Test
void testSomething() {
    // Arrange
    String input = "test";
    
    // Act
    String result = service.process(input);
    
    // Assert
    assertEquals("expected", result);
}
```

---

**Dernière mise à jour:** 2024  
**Auteur:** Équipe Transcendence
