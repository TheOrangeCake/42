/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:20:02 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/18 15:07:37 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// put pixel to screen
void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dest;

	x *= 20;
	y *= 20;
	dest = img->addr + (x * img->line_length + y * (img->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

// circle through points
void	create_image(t_data *img, t_point **map)
{
	int x;
	int y;

	x = 0;
	while (map[x] != NULL)
	{
 		y = 0;
		while (map[x][y].end != 1)
		{
			my_mlx_pixel_put(img, x, y, map[x][y].color);
			y++;
		}
		x++;
	}
}
