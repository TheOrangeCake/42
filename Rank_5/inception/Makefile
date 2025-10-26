# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 14:55:00 by hoannguy          #+#    #+#              #
#    Updated: 2025/07/18 11:14:14 by hoannguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DOCKER_COMPOSE = ./srcs/docker-compose.yml
ENV_FILE = ./srcs/.env
WORDPRESS_DATABASE = /home/hoannguy/data/wordpress
MARIADB_DATABASE = /home/hoannguy/data/mariadb

NAME = Inception

all: dir build up logs

dir:
	@sudo mkdir -p $(WORDPRESS_DATABASE)
	@sudo mkdir -p $(MARIADB_DATABASE)
	@sudo chown -R $(USER):$(USER) $(WORDPRESS_DATABASE) $(MARIADB_DATABASE)
	@sudo chmod -R 755 $(WORDPRESS_DATABASE) $(MARIADB_DATABASE)
	@echo "Folders for database created"

build:
	@sudo docker compose -f $(DOCKER_COMPOSE) --env-file $(ENV_FILE) build
	@echo "Images built"

up:
	@sudo docker compose -f $(DOCKER_COMPOSE) --env-file $(ENV_FILE) up -d
	@echo "Containers started"

down:
	@sudo docker compose -f $(DOCKER_COMPOSE) --env-file $(ENV_FILE) down
	@echo "Containers stopped"

fclean: down
	@sudo docker system prune -a -f --volumes
	@rm -rf $(WORDPRESS_DATABASE)/* $(WORDPRESS_DATABASE)/.* 2>/dev/null || true
	@rm -rf $(MARIADB_DATABASE)/* $(MARIADB_DATABASE)/.* 2>/dev/null || true
	@echo "All containers, images, networks and volumes removed"
	@echo "Database folders cleared"

re: fclean dir build up logs

show:
	@sudo docker compose -f $(DOCKER_COMPOSE) ps

logs:
	@docker compose -f $(DOCKER_COMPOSE) logs -f

.PHONY: all dir build up down fclean re show
