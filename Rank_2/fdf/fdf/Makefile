NAME = fdf

SOURCE = main.c check_map.c fill_map.c

HEADER = fdf.h

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))

# Compile libft

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

#

# Compile minilibX

MINILIBX_PATH = ./minilibx_linux
MINILIBX = $(MINILIBX_PATH)/libmlx.a
$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_PATH)

#

GCC = gcc
# FLAGS = -Wextra -Wall -Werror
FLAGS =
RM = rm -f

all : $(LIBFT) $(MINILIBX) $(NAME)

$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(OBJ_DIR)
	@$(GCC) $(FLAGS) -I$(LIBFT_PATH)/includes -I$(MINILIBX_PATH) -c $< -o $@

$(NAME):	$(OBJECTS)
	@$(GCC) $(FLAGS) $(OBJECTS) -L$(MINILIBX_PATH) -lmlx -L$(LIBFT_PATH) -lft -lXext -lX11 -lm -lz -o $(NAME)
	@echo "Built $(NAME)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@echo "Deleted object files"

fclean:		clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(MAKE) -C $(MINILIBX_PATH) clean
	@echo "Deleted $(NAME)"

re: fclean all

.PHONY: all clean fclean re