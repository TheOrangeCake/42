#!/bin/bash

# Load env variables
export $(grep -v '^#' .env | xargs)

# Run Spring Boot
./mvnw spring-boot:run -Dspring-boot.run.profiles=dev
