#!/bin/bash

docker build -t api42-service .
docker run --env-file .env -p 4444:4444 api42-service
