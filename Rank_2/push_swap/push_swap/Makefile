NAME = push_swap

SOURCE = main.c helper1.c helper2.c move1.c move2.c smallsorts1.c smallsorts2.c smallsorts3.c quicksort.c quicksort_next.c

S_BONUS = checker_main.c helper1.c helper2.c checker_move1.c checker_move2.c

HEADER = pushswap.h

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))

# Compile libft

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

#

GCC = gcc
# FLAGS = -Wextra -Wall -Werror
FLAGS =
RM = rm -f

all : $(LIBFT) $(NAME)

$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(OBJ_DIR)
	@$(GCC) $(FLAGS) -I$(LIBFT_PATH)/includes -c $< -o $@

$(NAME):	$(OBJECTS)
	@$(GCC) $(FLAGS) $(OBJECTS) -L$(LIBFT_PATH) -lft -o $(NAME)
	@echo "Built $(NAME)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@echo "Deleted object files"

fclean:		clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@echo "Deleted $(NAME)"

re: fclean all

.PHONY: all clean fclean re