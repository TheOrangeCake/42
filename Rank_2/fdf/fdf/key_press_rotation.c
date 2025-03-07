/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:16:53 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/05 11:03:13 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	z_rotate(t_params *params)
{
	params -> switch_z = 1;
	params -> rotate_z += 1 * (M_PI / 180);
	reset_map(params);
	update_map(params);
	if (params -> projection == 1)
		isometric(params);
	if (params -> projection == 0)
		military(params, params -> d);
	if (params -> projection == 2)
		find_coordinates(params -> new_map, params -> row, params -> column);
	make_image_helper(params);
	params -> switch_z = 0;
}

void	x_rotate(t_params *params)
{
	params -> switch_x = 1;
	params -> rotate_x += 1 * (M_PI / 180);
	reset_map(params);
	update_map(params);
	if (params -> projection == 1)
		isometric(params);
	if (params -> projection == 0)
		military(params, params -> d);
	if (params -> projection == 2)
		find_coordinates(params -> new_map, params -> row, params -> column);
	make_image_helper(params);
	params -> switch_x = 0;
}

void	y_rotate(t_params *params)
{
	params -> switch_y = 1;
	params -> rotate_y += 1 * (M_PI / 180);
	reset_map(params);
	update_map(params);
	if (params -> projection == 1)
		isometric(params);
	if (params -> projection == 0)
		military(params, params -> d);
	if (params -> projection == 2)
		find_coordinates(params -> new_map, params -> row, params -> column);
	make_image_helper(params);
	params -> switch_y = 0;
}

void	x_rotate_counter(t_params *params)
{
	params -> switch_x = 2;
	params -> rotate_x -= 1 * (M_PI / 180);
	reset_map(params);
	update_map(params);
	if (params -> projection == 1)
		isometric(params);
	if (params -> projection == 0)
		military(params, params -> d);
	if (params -> projection == 2)
		find_coordinates(params -> new_map, params -> row, params -> column);
	make_image_helper(params);
	params -> switch_x = 0;
}

void	y_rotate_counter(t_params *params)
{
	params -> switch_y = 2;
	params -> rotate_y -= 1 * (M_PI / 180);
	reset_map(params);
	update_map(params);
	if (params -> projection == 1)
		isometric(params);
	if (params -> projection == 0)
		military(params, params -> d);
	if (params -> projection == 2)
		find_coordinates(params -> new_map, params -> row, params -> column);
	make_image_helper(params);
	params -> switch_y = 0;
}
