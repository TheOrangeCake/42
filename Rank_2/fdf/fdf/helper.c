/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:49:47 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 18:24:19 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_map_helper(t_params *params)
{
	params -> fd = open("test.fdf", O_RDONLY);
	params -> map = fill_map(params);
	close(params -> fd);
}

void	make_image_helper(t_params *params)
{
	params -> img = mlx_new_image(params -> mlx, WIDTH, HEIGHT);
	params -> addr = mlx_get_data_addr(params -> img, &params -> bits_per_pixel,
			&params -> line_length, &params -> endian);
	create_image(params);
	mlx_put_image_to_window(params -> mlx,
		params -> window, params -> img, 0, 0);
}

void	scroll_down(t_params *params)
{
	int	a;
	int	b;

	a = 0;
	params -> scale = 1.1;
	while (a < params -> row)
	{
		b = 0;
		while (b < params -> column)
		{
			params -> map[a][b].x /= params -> scale;
			params -> map[a][b].y /= params -> scale;
			b++;
		}
		a++;
	}
}

void	scroll_up(t_params *params)
{
	int	a;
	int	b;

	a = 0;
	params -> scale = 1.1;
	while (a < params -> row)
	{
		b = 0;
		while (b < params -> column)
		{
			params -> map[a][b].x *= params -> scale;
			params -> map[a][b].y *= params -> scale;
			b++;
		}
		a++;
	}
}
