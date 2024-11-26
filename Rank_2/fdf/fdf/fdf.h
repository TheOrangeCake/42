/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:38:16 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/26 18:49:05 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include "libft.h"
#include "mlx.h"
#include <math.h>

# ifndef WIDTH
# define WIDTH 1920
# endif

# ifndef HEIGHT
# define HEIGHT 1080
# endif

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_point
{
	int	y;
	int	x;
	int	z;
	int	color;
}	t_point;

typedef struct	s_bresenham
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

typedef struct	s_color
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

void	free_split(char **array);
t_point	**start_map(int fd, int *row, int *colunm);
t_point	**fill_map(t_point **map, int fd, int *row, int *column);
void	create_image(t_data *img, t_point **map, int *row, int *column);
void	bresenham(t_data *img, t_point point0, t_point point1);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
void	isometric(t_point **map, int row, int column);
int	interpolating_color(t_point point1, t_point point0, t_bresenham line);
int		step(t_bresenham line);

#endif
