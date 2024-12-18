/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:55:57 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/18 17:31:43 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_window(t_params *params)
{
	while (params -> row > 0)
	{
		free((params -> map)[params -> row - 1]);
		params -> row--;
	}
	free(params -> map);
	mlx_destroy_window(params -> mlx, params -> window);
	ft_printf("Program terminated\n");
	exit(0);
}

void	iso_projection(t_params *params)
{
	fill_map_helper(params);
	isometric(params);
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}

void	mili_projection(t_params *params)
{
	fill_map_helper(params);
	military(params, params -> d);
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}

void	flat_projection(t_params *params)
{
	flat(params);
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}

void	change_color(t_params *params)
{
	params->color_change = (params->color_change + 1050) % 16777216;
	fill_map_helper(params);
	if (params -> projection == 1)
		isometric(params);
	if (params -> projection == 0)
		military(params, params -> d);
	if (params -> projection == 2)
		find_coordinates(params -> map, params -> row, params -> column);
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}
