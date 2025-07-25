# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/15 14:19:38 by maw               #+#    #+#              #
#    Updated: 2025/06/07 21:02:42 by hoannguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = 	ft_isalpha.c \
		ft_isalnum.c \
		ft_isdigit.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_atoi.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_itoa.c \
		ft_strncmp.c \
		ft_strjoin.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strlcat.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_memcmp.c \
		ft_memchr.c \
		ft_strnstr.c \
		ft_bzero.c \
		ft_strdup.c \
		ft_substr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c \
		ft_calloc.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strtrim.c \
		ft_split.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_lstadd_front.c \
		ft_lstlast.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		
		

OBJS := $(SRCS:%.c=%.o)

FLAGS = -Wall -Werror -Wextra

RM = rm -f

$(NAME):
	@gcc $(FLAGS) -c $(SRCS) -I ./
	@ar rc $(NAME) $(OBJS)

all: $(NAME)

clean :
	@$(RM) $(OBJS)
	
fclean: clean
	@$(RM) $(NAME)

re: fclean all

bonus: $(NAME)