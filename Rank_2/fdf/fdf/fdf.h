/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:38:16 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/18 12:29:04 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <math.h>

# define ESC_KEY 65307
# define n1_KEY 49
# define n2_KEY 50
# define n3_KEY 51
# define n4_KEY 52
# define n5_KEY 53
# define n6_KEY 54
# define n7_KEY 55
# define n8_KEY 56
# define n9_KEY 57
# define n0_KEY 48
# define G_KEY 103
# define H_KEY 104
# define J_KEY 105
# define ARROW_UP 65362
# define W_KEY 119
# define ARROW_DOWN 65364
# define S_KEY 115
# define ARROW_LEFT 65361
# define A_KEY 97
# define ARROW_RIGHT 65363
# define D_KEY 100
# define SCROLL_UP 4
# define SCROLL_DOWN 5

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

typedef struct s_point
{
	int	y;
	int	x;
	int	z;
	int	color;
}	t_point;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color0;
	int	color1;
	int	step;
	int	current_step;
}	t_bresenham;

typedef struct s_color
{
	int	color;
	int	red0;
	int	green0;
	int	blue0;
	int	red1;
	int	green1;
	int	blue1;
	int	red_new;
	int	green_new;
	int	blue_new;
}	t_color;

typedef struct s_save_line
{
	int	min_x;
	int	min_y;
}	t_save_line;

typedef struct s_params
{
	void	*mlx;
	void	*window;
	int		fd;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_point	**map;
	int		row;
	int		column;
	char	*line;
	char	**array;
	int		x;
	int		y;
	float	s_x;
	float	s_y;
	float	s_z;
	int		projection;
	int		color_change;
}	t_params;

// helper
void	free_split(char **array);
t_point	**start_map(int fd, int *row, int *colunm);
t_point	**fill_map(t_params *params);
void	create_image(t_params *params);
void	fill_map_helper(t_params *params);
void	make_image_helper(t_params *params);
void	iso_projection(t_params *params);
void	mili_projection(t_params *params);
void	flat_projection(t_params *params);
void	scroll_up(t_params *params);
void	scroll_down(t_params *params);
// draw
void	bresenham(t_params *params, t_point point0, t_point point1);
void	my_mlx_pixel_put(t_params *params, int x, int y, int color);
void	isometric(t_params *params);
void	military(t_params *params, float d);
void	flat(t_params *params);
int		interpolating_color(t_point point1, t_point point0, t_bresenham line);
int		step(t_bresenham line);
// hook
int		key_press(int keycode, t_params *params);
int		x_close_window(int x11_event, t_params *params);
int		mouse_scroll(int button, int x, int y, t_params *params);
void	close_window(t_params *params);
void	projection(t_params params);
void	move_up(t_params *params);
void	move_down(t_params *params);
void	move_right(t_params *params);
void	move_left(t_params *params);
void	y_rotate_counter(t_params *params);
void	change_color(t_params *params);
void	find_coordinates(t_point **map, int row, int column);

#endif
