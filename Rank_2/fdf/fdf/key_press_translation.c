/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_translation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:11:39 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/18 11:52:49 by hoannguy         ###   ########.fr       */
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
			params -> map[a][b].x -= 10;
			params -> map[a][b].y;
			b++;
		}
		a++;
	}
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
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
			params -> map[a][b].x += 10;
			params -> map[a][b].y;
			b++;
		}
		a++;
	}
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
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
			params -> map[a][b].x;
			params -> map[a][b].y -= 10;
			b++;
		}
		a++;
	}
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
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
			params -> map[a][b].x;
			params -> map[a][b].y += 10;
			b++;
		}
		a++;
	}
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}

void	y_rotate_counter(t_params *params)
{
	int		a;
	int		b;
	double	temp_x;
	double	temp_y;

	a = 0;
	while (a < params -> row)
	{
		b = 0;
		while (b < params -> column)
		{
			temp_x = params->map[a][b].x * cos(M_PI / 4) - params->map[a][b].y * sin(M_PI / 10);
            temp_y = params->map[a][b].x * sin(M_PI / 4) + params->map[a][b].y * cos(M_PI / 10);
			params->map[a][b].x = temp_x;
            params->map[a][b].y = temp_y;
			// params -> map[a][b].x = params -> map[a][b].x * cos(M_PI / 4) - params -> map[a][b].y * sin(M_PI /10);
			// params -> map[a][b].y = params -> map[a][b].x * sin(M_PI / 4) + params -> map[a][b].y * cos(M_PI /10);
			b++;
		}
		a++;
	}
	isometric(params);
	mlx_clear_window(params -> mlx, params -> window);
	mlx_destroy_image(params->mlx, params->img);
	make_image_helper(params);
}
