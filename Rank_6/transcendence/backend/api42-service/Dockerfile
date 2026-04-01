# Build stage -> copy pom -> download dependency -> copy files -> build *.jar
FROM maven:3.9-eclipse-temurin-17-alpine AS build
WORKDIR /app
COPY pom.xml .
RUN mvn -q -DskipTests dependency:go-offline
COPY src ./src
RUN mvn -q -DskipTests package

# Run stage -> set up user -> copy *.jar -> run *.jar
FROM eclipse-temurin:17-jre
RUN groupadd spring && useradd -r -g spring spring
RUN mkdir -p /opt/app && \
    chown spring:spring /opt/app
RUN mkdir -p /app/uploads && \
    chown spring:spring /app/uploads && \
    chmod 755 /app/uploads
COPY --from=build /app/target/*.jar /opt/app/app.jar
COPY --chown=spring:spring src/main/resources/static/default_images /app/uploads
USER spring
EXPOSE 8084
ENTRYPOINT ["java", "-jar", "/opt/app/app.jar"]