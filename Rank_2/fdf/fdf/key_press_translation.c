/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_translation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:11:39 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/23 17:11:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_up(t_params *params)
{
	int	a;
	int	b;

	a = 0;
	while (a < params -> row)
	{
		b = 0;
		while (b < params -> column)
		{
			params -> new_map[a][b].x -= 10;
			b++;
		}
		a++;
	}
	mlx_destroy_image(params -> mlx, params -> img);
	make_image_helper(params);
}

void	move_down(t_params *params)
{
	int	a;
	int	b;

	a = 0;
	while (a < params -> row)
	{
		b = 0;
		while (b < params -> column)
		{
			params -> new_map[a][b].x += 10;
			b++;
		}
		a++;
	}
	mlx_destroy_image(params -> mlx, params -> img);
	make_image_helper(params);
}

void	move_left(t_params *params)
{
	int	a;
	int	b;

	a = 0;
	while (a < params -> row)
	{
		b = 0;
		while (b < params -> column)
		{
			params -> new_map[a][b].y -= 10;
			b++;
		}
		a++;
	}
	mlx_destroy_image(params -> mlx, params -> img);
	make_image_helper(params);
}

void	move_right(t_params *params)
{
	int	a;
	int	b;

	a = 0;
	while (a < params -> row)
	{
		b = 0;
		while (b < params -> column)
		{
			params -> new_map[a][b].y += 10;
			b++;
		}
		a++;
	}
	mlx_destroy_image(params -> mlx, params -> img);
	make_image_helper(params);
}

void	z_rotate_counter(t_params *params)
{
	params -> switch_z = 2;
	params -> rotate_z -= 1 * (M_PI / 180);
	reset_map(params);
	update_map(params);
	if (params -> projection == 1)
		isometric(params);
	if (params -> projection == 0)
		military(params, params -> d);
	if (params -> projection == 2)
		find_coordinates(params -> new_map, params -> row, params -> column);
	mlx_destroy_image(params -> mlx, params -> img);
	make_image_helper(params);
	params -> switch_z = 0;
}
