SOURCE_PRINT = ft_printf.c ft_printf_helper.c

OBJECTS_PRINT = ${SOURCE_PRINT:.c=.o}

NAME = libftprintf.a

HEADER = ft_printf.h

LIBFT_PATH = ./libft
LIBFT = ${LIBFT_PATH}/libft.a
${LIBFT}:
	${MAKE} -C ${LIBFT_PATH} bonus

AR = ar rc
INDEX = ranlib
RM = rm -f
GCC = gcc
FLAGS = -Wall -Wextra -Werror

all:	${NAME}

.c.o:
	${GCC} ${FLAGS} -c -I ${HEADER} $< -o ${<:.c=.o}

${NAME}: 	${LIBFT} ${OBJECTS_PRINT}
	cp ${LIBFT} ${NAME}
	${AR} ${NAME} ${OBJECTS_PRINT}
	${INDEX} ${NAME}

clean:	
	${MAKE} -C ${LIBFT_PATH} clean
	${RM} ${OBJECTS} ${OBJECTS_PRINT}

fclean:		clean
	${MAKE} -C ${LIBFT_PATH} fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

