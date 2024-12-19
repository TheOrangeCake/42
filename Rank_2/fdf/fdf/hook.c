/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:42:06 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/19 15:28:46 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_press_helper(int keycode, t_params *params)
{
	if (keycode == N4_KEY)
		x_rotate_counter(params);
	if (keycode == N5_KEY)
		x_rotate(params);
	if (keycode == N6_KEY)
		y_rotate_counter(params);
	if (keycode == N7_KEY)
		y_rotate(params);
	if (keycode == N8_KEY)
		z_rotate_counter(params);
	if (keycode == N9_KEY)
		z_rotate(params);
}

int	key_press(int keycode, t_params *params)
{
	ft_printf("key: %d\n", keycode);
	if (keycode == ESC_KEY)
		close_window(params);
	if (keycode == N1_KEY)
		iso_projection(params);
	if (keycode == N2_KEY)
		mili_projection(params);
	if (keycode == N3_KEY)
		flat_projection(params);
	if (keycode == W_KEY || keycode == ARROW_UP)
		move_up(params);
	if (keycode == S_KEY || keycode == ARROW_DOWN)
		move_down(params);
	if (keycode == A_KEY || keycode == ARROW_LEFT)
		move_left(params);
	if (keycode == D_KEY || keycode == ARROW_RIGHT)
		move_right(params);
	if (keycode == N0_KEY)
		change_color(params);
	if (keycode == N4_KEY || keycode == N5_KEY || keycode == N6_KEY
		|| keycode == N7_KEY || keycode == N8_KEY || keycode == N9_KEY)
		key_press_helper(keycode, params);
	return (0);
}

int	x_close_window(t_params *params)
{
	while (params -> row > 0)
	{
		free((params -> map)[params -> row - 1]);
		free((params -> new_map)[params -> row - 1]);
		params -> row--;
	}
	free(params -> map);
	free(params -> new_map);
	mlx_destroy_window(params -> mlx, params -> window);
	ft_printf("Program terminated\n");
	exit(0);
}

int	mouse_scroll(int button, int x, int y, t_params *params)
{
	(void)x;
	(void)y;
	if (button == SCROLL_UP)
	{
		params -> s_x *= 1.1;
		params -> s_y *= 1.1;
		params -> s_z *= 1.1;
	}
	if (button == SCROLL_DOWN)
	{
		params -> s_x /= 1.1;
		params -> s_y /= 1.1;
		params -> s_z /= 1.1;
	}
	if (params -> projection == 1)
		iso_projection(params);
	if (params -> projection == 0)
		mili_projection(params);
	if (params -> projection == 2)
		flat_projection(params);
	return (0);
}
