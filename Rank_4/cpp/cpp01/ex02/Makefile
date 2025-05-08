.DEFAULT_GOAL := all

NAME = reference

SOURCE = main.cpp

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCE:.cpp=.o))

GCC = g++
FLAGS = -Wextra -Wall -Werror -std=c++98
# FLAGS =
RM = rm -f

all : $(NAME)

$(OBJ_DIR)/%.o:%.cpp
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