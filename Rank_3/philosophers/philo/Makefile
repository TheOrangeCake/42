.DEFAULT_GOAL := all

NAME = philo

SOURCE = main.c case_of_one.c philo.c helper1.c helper2.c

HEADER = philo.h

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))

# Compile libft

# LIBFT_PATH = ./libft
# LIBFT = $(LIBFT_PATH)/libft.a
# $(LIBFT):
# 	@$(MAKE) -C $(LIBFT_PATH)

#

GCC = gcc
FLAGS = -Wextra -Wall -Werror -pthread
# FLAGS = -pthread
RM = rm -f

all : $(NAME)

$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(OBJ_DIR)
	@$(GCC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJECTS)
	@$(GCC) $(FLAGS) $(OBJECTS) -o $(NAME)
	@echo "Built $(NAME)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "Deleted object files"

fclean:		clean
	@$(RM) $(NAME)
	@echo "Deleted $(NAME)"

re: fclean all

.PHONY: all clean fclean re