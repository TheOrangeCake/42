COMPOSE = docker compose -f infra/docker-compose.yml --env-file .env

.PHONY: rebuild up down restart logs ps build clean setup-certs no-cache

rebuild: setup-certs
	$(COMPOSE) up -d --build

no-cache:
	$(COMPOSE) build --no-cache
	$(COMPOSE) up -d

setup-certs:
	@bash infra/scripts/setup-certs.sh
	
up: setup-certs
	$(COMPOSE) up -d

down:
	$(COMPOSE) down

restart:
	$(COMPOSE) down
	$(COMPOSE) up -d --build

logs:
	$(COMPOSE) logs -f --tail=200

ps:
	$(COMPOSE) ps

build:
	$(COMPOSE) build

clean:
	$(COMPOSE) down -v
