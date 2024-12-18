/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:42:06 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/18 12:03:52 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// ESC	: close window
// I	: isometric projection
// M	: military projection
// F	: 2D projection
// W arrow up 		: move up
// S arrow down	: move down
// A arrow left	: move left
// D arrow right	: move right
// Y	: rotate y axis counter
// G	: rotate x axis clockwise
// H	: rotate y axis counter
// J	: rotate x axis clockwise

int	key_press(int keycode, t_params *params)
{
	ft_printf("key: %d\n", keycode);
	if (keycode == ESC_KEY)
		close_window(params);
	if (keycode == n1_KEY)
		iso_projection(params);
	if (keycode == n2_KEY)
		mili_projection(params);
	if (keycode == n3_KEY)
		flat_projection(params);
	if (keycode == W_KEY || keycode == ARROW_UP)
		move_up(params);
	if (keycode == S_KEY || keycode == ARROW_DOWN)
		move_down(params);
	if (keycode == A_KEY || keycode == ARROW_LEFT)
		move_left(params);
	if (keycode == D_KEY || keycode == ARROW_RIGHT)
		move_right(params);
	if (keycode == n4_KEY)
		y_rotate_counter(params);
	if (keycode == n0_KEY)
		change_color(params);
	return (0);
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
		params -> s_x *= 1.1;
		params -> s_y *= 1.1;
		params -> s_z *= 1.1;
		if (params -> projection == 1)
			iso_projection(params);
		if (params -> projection == 0)
			mili_projection(params);
		if (params -> projection == 2)
			flat_projection(params);
	}
	if (button == SCROLL_DOWN)
	{
		params -> s_x /= 1.1;
		params -> s_y /= 1.1;
		params -> s_z /= 1.1;
		if (params -> projection == 1)
			iso_projection(params);
		if (params -> projection == 0)
			mili_projection(params);
		if (params -> projection == 2)
			flat_projection(params);
	}
	return (0);
}
