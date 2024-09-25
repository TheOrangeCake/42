SOURCE = ft_putchar.c ft_putstr.c ft_strcmp.c ft_strlen.c ft_swap.c

PATH = ${addprefix ./srcs/, ${SOURCE}}

HEADER = ./includes/

OBJECTS = ${PATH:.c=.o}

NAME = libft.a

AR = ar rc
RM = rm -f
INDEX = ranlib
GCC = gcc
CFLAGS = -Wall -Wextra -Werror

all:	${NAME}

.c.o
		${GCC} ${CFLAGS} -c -I ${HEADER} -o $< ${<:.c=.o}