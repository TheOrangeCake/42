/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:20:02 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/20 10:53:00 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// put pixel to screen
void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (x * img->line_length + y * (img->bits_per_pixel / 8));
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		*(unsigned int *)dest = color;
}

void	draw_horizontal(t_data *img, t_point **map, int *row, int *column)
{
	int	x;
	int	y;

	x = 0;
	while (x < *row)
	{
		y = 0;
		while (y < *column - 1)
		{
			bresenham(img, map[x][y], map[x][y + 1]);
			y++;
		}
		x++;
	}
}

void	draw_vertical(t_data *img, t_point **map, int *row, int *column)
{
	int	x;
	int	y;

	y = 0;
	while (y < *column)
	{
		x = 0;
		while (x < *row - 1)
		{
			bresenham(img, map[x][y], map[x + 1][y]);
			x++;
		}
		y++;
	}
}

// circle through points
void	create_image(t_data *img, t_point **map, int *row, int *column)
{
	int	x;
	int	y;

	x = 0;
	while (x < *row)
	{
		y = 0;
		while (y < *column)
		{
			my_mlx_pixel_put(img, map[x][y].x, map[x][y].y, map[x][y].color);
			y++;
		}
		x++;
	}
	// draw_horizontal(img, map, row, column);
	// draw_vertical(img, map, row, column);
}
