/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:55:57 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/19 15:26:48 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_window(t_params *params)
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

void	iso_projection(t_params *params)
{
	reset_map(params);
	update_map(params);
	isometric(params);
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}

void	mili_projection(t_params *params)
{
	reset_map(params);
	update_map(params);
	military(params, params -> d);
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}

void	flat_projection(t_params *params)
{
	reset_map(params);
	update_map(params);
	flat(params);
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}

void	change_color(t_params *params)
{
	params->color_change = (params->color_change + 1050) % 16777216;
	reset_map(params);
	update_map(params);
	if (params -> projection == 1)
		isometric(params);
	if (params -> projection == 0)
		military(params, params -> d);
	if (params -> projection == 2)
		flat(params);
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}
