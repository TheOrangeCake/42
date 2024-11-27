/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:42:06 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 16:28:38 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_params *params)
{
	// ft_printf("key: %d\n", keycode);
	if (keycode == ESC_KEY)
		close_window(params);
	if (keycode == I_KEY)
	{
		fill_map_helper(params);
		isometric(params -> map, params -> row, params -> column);
		mlx_clear_window(params -> mlx, params -> window);
		mlx_destroy_image(params->mlx, params->img);
		params->img = mlx_new_image(params->mlx, WIDTH, HEIGHT);
		params->addr = mlx_get_data_addr(params->img, &params->bits_per_pixel, &params->line_length, &params->endian);
		create_image(params);
		mlx_put_image_to_window(params -> mlx, params -> window, params -> img, 0, 0);
	}
	if (keycode == M_KEY)
	{
		fill_map_helper(params);
		military(params -> map, params -> row, params -> column, (M_PI / 4));
		mlx_clear_window(params -> mlx, params -> window);
		mlx_destroy_image(params->mlx, params->img);
		params->img = mlx_new_image(params->mlx, WIDTH, HEIGHT);
		params->addr = mlx_get_data_addr(params->img, &params->bits_per_pixel, &params->line_length, &params->endian);
		create_image(params);
		mlx_put_image_to_window(params -> mlx, params -> window, params -> img, 0, 0);
	}
}

int	x_close_window(int x11_event, t_params *params)
{
	// while (map -> row > 0)
	// {
	// 	free((map -> map)[map -> row - 1]);
	// 	map -> row--;
	// }
	// free(map -> map);
	ft_printf("Program terminated\n");
	exit(0);
	return (0);
}

int	mouse_scroll(int button, int x, int y, t_params *params)
{
	int	a;
	int	b;

	if (button == SCROLL_UP)
	{
		a = 0;
		ft_printf("I am scrolling up\n");
		while (a < params -> row)
		{
			b = 0;
			while (b < params -> column)
			{
				params -> map[a][b].x *= 1.1;
				params -> map[a][b].y *= 1.1;
				b++; 
			}
			a++;
		}
		mlx_clear_window(params -> mlx, params -> window);
		mlx_destroy_image(params->mlx, params->img);
		params->img = mlx_new_image(params->mlx, WIDTH, HEIGHT);
		params->addr = mlx_get_data_addr(params->img, &params->bits_per_pixel, &params->line_length, &params->endian);
		create_image(params);
		mlx_put_image_to_window(params -> mlx, params -> window, params -> img, 0, 0);
	}
	if (button == SCROLL_DOWN)
	{
		a = 0;
		ft_printf("old %d\n", params -> map[1][1].x);
		while (a < params -> row)
		{
			b = 0;
			while (b < params -> column)
			{
				params -> map[a][b].x /= 1.1;
				params -> map[a][b].y /= 1.1;
				b++; 
			}
			a++;
		}
		mlx_clear_window(params -> mlx, params -> window);
		mlx_destroy_image(params->mlx, params->img);
		params->img = mlx_new_image(params->mlx, WIDTH, HEIGHT);
		params->addr = mlx_get_data_addr(params->img, &params->bits_per_pixel, &params->line_length, &params->endian);
		create_image(params);
		mlx_put_image_to_window(params -> mlx, params -> window, params -> img, 0, 0);
	}
	return (0);
}
