/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:41:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/25 01:00:28 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	camera_reset(t_params *params)
{
	params->camera.pos.x = 0;
	params->camera.pos.y = 0;
	params->camera.pos.z = -70;
	params->camera.vector.a = 0;
	params->camera.vector.b = 0;
	mlx_destroy_image(params->mlx, params->data.img);
	render(params);
}

int	key_press(int keycode, t_params *params)
{
	if (keycode == ESC_KEY)
		x_close_window(params);
	else if (keycode == W)
		camera_pos_up(params);
	else if (keycode == S)
		camera_pos_down(params);
	else if (keycode == A)
		camera_pos_left(params);
	else if (keycode == D)
		camera_pos_right(params);
	else if (keycode == Q)
		camera_pos_forward(params);
	else if (keycode == E)
		camera_pos_backward(params);
	else if (keycode == T)
		camera_look_up(params);
	else if (keycode == G)
		camera_look_down(params);
	else if (keycode == F)
		camera_look_left(params);
	else if (keycode == H)
		camera_look_right(params);
	else if (keycode == R)
		camera_reset(params);
	return (0);
}

int	x_close_window(t_params *params)
{
	free_maps(params);
	free_all(params);
	mlx_destroy_image(params->mlx, params->data.img);
	mlx_destroy_window(params->mlx, params->window);
	mlx_destroy_display(params->mlx);
	free(params->mlx);
	printf("Program terminated\n");
	exit(0);
}

void	hook(t_params *params)
{
	mlx_hook(params -> window, 2, 1L << 0, key_press, params);
	mlx_hook(params -> window, 33, 1L << 0, x_close_window, params);
}
