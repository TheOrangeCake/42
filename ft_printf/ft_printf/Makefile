SOURCE = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SOURCE_PRINT = ft_printf.c ft_printf_helper.c

PATH = ${addprefix ./srcs/, ${SOURCE}}

HEADER =  ./includes/

OBJECTS = ${PATH:.c=.o}

OBJECTS_PRINT = ${SOURCE_PRINT:.c=.o}

NAME_PRINTF = libftprintf.a

AR = ar rc
INDEX = ranlib
RM = rm -f
GCC = gcc
FLAGS = -Wall -Wextra -Werror

all:	${NAME_PRINTF}

.c.o:
	${GCC} ${FLAGS} -c -I ${HEADER} $< -o ${<:.c=.o}

${NAME_PRINTF}: ${OBJECTS} ${OBJECTS_PRINT}
	${AR} ${NAME_PRINTF} ${OBJECTS_PRINT}
	${INDEX} ${NAME_PRINTF}

clean:
	${RM} ${OBJECTS} ${OBJECTS_PRINT}

fclean:		clean
	${RM} ${NAME_PRINTF}

re: fclean all

.PHONY: all clean fclean re bonus
