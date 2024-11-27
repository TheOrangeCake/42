/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:20:02 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 12:59:09 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// put pixel to screen
void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dest;

	if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH)
	{
		dest = img->addr + (x * img->line_length + y
				* (img->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}

void	draw_horizontal(t_data *img, t_map map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map.row)
	{
		y = 0;
		while (y < map.column - 1)
		{
			bresenham(img, map.map[x][y], map.map[x][y + 1]);
			y++;
		}
		x++;
	}
}

void	draw_vertical(t_data *img, t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.column)
	{
		x = 0;
		while (x < map.row - 1)
		{
			bresenham(img, map.map[x][y], map.map[x + 1][y]);
			x++;
		}
		y++;
	}
}

// circle through points
void	create_image(t_data *img, t_map map)
{
	draw_horizontal(img, map);
	draw_vertical(img, map);
}

	// int	x;
	// int	y;

	// x = 0;
	// while (x < *row)
	// {
	// 	y = 0;
	// 	while (y < *column)
	// 	{
	// 		my_mlx_pixel_put(img, map[x][y].x, map[x][y].y, map[x][y].color);
	// 		y++;
	// 	}
	// 	x++;
	// }