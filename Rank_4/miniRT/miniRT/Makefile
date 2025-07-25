# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 12:39:32 by masase            #+#    #+#              #
#    Updated: 2025/07/11 17:03:48 by hoannguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = 	srcs/main.c \
		srcs/free_all.c srcs/free_all2.c srcs/hook.c srcs/hook2.c srcs/hook3.c srcs/hook4.c\
		srcs/vector.c srcs/vector2.c srcs/vector3.c \
		srcs/image_start.c srcs/image_create.c srcs/image_get_color.c\
		srcs/inter_sphere.c srcs/inter_plane.c srcs/inter_cylinder.c srcs/inter_cylinder_cap.c srcs/inter_cone.c srcs/inter_cone_cap.c\
		srcs/light_ambient.c srcs/light_diffuse.c srcs/light_specular.c\
		srcs/shadow.c srcs/shadow_sphere.c srcs/shadow_plane.c srcs/shadow_cylinder.c srcs/shadow_cone.c\
		srcs/pattern_checkerboard.c srcs/pattern_stripe.c srcs/pattern_planets.c\
		srcs/bump_initialise.c srcs/bump_sphere.c\
		srcs/parsing/parsing.c \
		srcs/parsing/fill_struct.c \
		srcs/parsing/save_ambiance.c \
		srcs/parsing/save_camera.c \
		srcs/parsing/save_light.c \
		srcs/parsing/save_plane.c \
		srcs/parsing/save_sphere.c \
		srcs/parsing/save_cylinder.c srcs/parsing/save_cylinder_utils.c \
		srcs/parsing/save_cone.c srcs/parsing/save_cone_utils.c\
		srcs/parsing/save_utils.c \
		srcs/parsing/save_utils2.c \
		srcs/parsing/utils.c \
		srcs/parsing/utils_2.c \
		srcs/parsing/error_message.c \
		srcs/parsing/print_struct.c \
		srcs/parsing/print_struct2.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Werror -Wextra -g3

RM = rm -f

LIBFT_PATH = libft/

LIBFT_LIB = $(LIBFT_PATH)/libft.a

MLX_PATH = minilibx-linux/

MLX_LIB = $(MLX_PATH)libmlx_Linux.a

MLX_FLAGS = -Lminilibx-linux -L/usr/lib/X11 -lXext -lX11

$(NAME): subsystems $(OBJS)
		@gcc $(FLAGS) $(OBJS) $(MLX_LIB) $(LIBFT_LIB) $(MLX_FLAGS) -lm -o $(NAME)
		@echo "made $(NAME)"

%.o: %.c 
		@gcc $(FLAGS) -c $< -o $@

subsystems: 
		@make -C $(MLX_PATH) all
		@make -C $(LIBFT_PATH) all
		@echo "dependencies compiled"

all: $(NAME)

clean:
		$(RM) $(OBJS)
		@make -C $(LIBFT_PATH) clean
		@make -C $(MLX_PATH) clean
		@echo "delete object files"

		
fclean: clean
		$(RM) $(NAME)
		@make -C $(LIBFT_PATH) fclean
		@make -C $(MLX_PATH) clean
		@echo "delete $(NAME)"

re: fclean all