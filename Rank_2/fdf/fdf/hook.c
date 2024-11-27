/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:42:06 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 18:16:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_params *params)
{
	// ft_printf("key: %d\n", keycode);
	if (keycode == ESC_KEY)
		close_window(params);
	if (keycode == I_KEY)
		iso_projection(params);
	if (keycode == M_KEY)
		mili_projection(params);
	if (keycode == F_KEY)
		flat_projection(params);
	if (keycode == W_KEY || keycode == ARROW_UP)
		move_up(params);
	if (keycode == S_KEY || keycode == ARROW_DOWN)
		move_down(params);
	if (keycode == A_KEY || keycode == ARROW_LEFT)
		move_left(params);
	if (keycode == D_KEY || keycode == ARROW_RIGHT)
		move_right(params);
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
	if (button == SCROLL_UP)
	{
		scroll_up(params);
		mlx_clear_window(params -> mlx, params -> window);
		mlx_destroy_image(params->mlx, params->img);
		make_image_helper(params);
	}
	if (button == SCROLL_DOWN)
	{
		scroll_down(params);
		mlx_clear_window(params -> mlx, params -> window);
		mlx_destroy_image(params->mlx, params->img);
		make_image_helper(params);
	}
	return (0);
}
