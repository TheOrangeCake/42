<span style="color:red">Config</span>

	-	Spring Cloud Gateway : Pour le routage, le filtrage et la modification des requêtes/réponses.

	-	Spring Boot Actuator : Indispensable pour surveiller l'état de santé (health) et les métriques de votre gateway.

	-	Spring Cloud Circuit Breaker (Resilience4j) : Pour éviter qu'une panne sur un microservice ne se propage (pattern "Circuit Breaker").

	-	Spring Boot Security + OAuth2 Client / Resource Server : Pour gérer l'authentification (souvent via JWT avec Keycloak ou Okta) directement à l'entrée.

	-	Spring Boot Validation : Pour valider les formats de données dès le point d'entrée.

	-	Spring Cloud LoadBalancer : Pour répartir la charge entre plusieurs instances d'un même service.

	-	Eureka Discovery Client (ou Consul/Zookeeper) : Pour que la Gateway "trouve" automatiquement vos microservices.

	-	Spring Cloud Config Client : Pour centraliser la configuration de vos routes sans redémarrer l'application.

	-	Micrometer Tracing + Zipkin/Jaeger : Pour suivre une requête (trace ID) à travers tous vos microservices.

	-	Prometheus : Pour collecter les métriques de performance.

<span style="color:green">Pour run l'API gateway : mvn spring-boot:run</span>