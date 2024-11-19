/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:38:16 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/19 16:33:58 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include "libft.h"
#include "mlx.h"

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
}	t_bresenham;

void	free_split(char **array);
t_point	**start_map(int fd, int *row, int *colunm);
t_point	**fill_map(t_point **map, int fd, int *row, int *column);
void	create_image(t_data *img, t_point **map, int *row, int *column);
void	bresenham(t_data *img, t_point point0, t_point point1);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);

#endif
