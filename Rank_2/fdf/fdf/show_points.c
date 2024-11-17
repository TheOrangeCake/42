/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:20:02 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/17 14:36:26 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// put pixel to screen
void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dest;

	x *= 20;
	y *= 20;
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

void	create_image(t_data *img, t_point **map)
{
	int x;
	int y;

	x = 0;
	while (map[x] != NULL)
	{
 		y = 0;
		while (map[x][y].end == NULL)
		{
			my_mlx_pixel_put(img, x, y, 0xffffff);
			y++;
		}
		x++;
	}
}