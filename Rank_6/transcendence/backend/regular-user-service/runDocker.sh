#!/bin/bash

docker build -t regular-user-service .
docker run --env-file .env -p 4445:4445 regular-user-service
