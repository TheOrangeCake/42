.DEFAULT_GOAL := all

NAME = pipex

N_BONUS = pipex

SOURCE = main.c children.c helper.c special_case.c

S_BONUS = bonus_main_bonus.c bonus_children_bonus.c bonus_helper_bonus.c special_case.c

HEADER = pipex.h

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))

OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(S_BONUS:.c=.o))

# Compile libft

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

#

GCC = gcc
FLAGS = -Wextra -Wall -Werror
# FLAGS =
RM = rm -f

all : $(LIBFT) $(NAME)

bonus : $(LIBFT) $(N_BONUS)

$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(OBJ_DIR)
	@$(GCC) $(FLAGS) -I$(LIBFT_PATH)/includes -c $< -o $@

$(NAME):	$(OBJECTS) $(LIBFT)
	@$(GCC) $(FLAGS) $(OBJECTS) -L$(LIBFT_PATH) -lft -o $(NAME)
	@echo "Built $(NAME)"

$(N_BONUS):	$(OBJ_BONUS)
	@$(GCC) $(FLAGS) $(OBJ_BONUS) -L$(LIBFT_PATH) -lft -o $(N_BONUS)
	@echo "Built $(N_BONUS)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@echo "Deleted object files"

fclean:		clean
	@$(RM) $(NAME) $(N_BONUS)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@echo "Deleted $(NAME) and $(N_BONUS)"

re: fclean all

.PHONY: all clean fclean re bonus