/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:42:06 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 15:32:49 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_params *params)
{
	// ft_printf("key: %d\n", keycode);
	if (keycode == ESC_KEY)
		close_window(params);
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
	int	a;
	int	b;

	if (button == SCROLL_UP)
	{
		a = 0;
		ft_printf("I am scrolling up\n");
		while (a < params -> row)
		{
			b = 0;
			while (y < params -> column)
			{
				params -> map[a][b].x *= 1.1;
				params -> map[a][b].y *= 1.1;
				b++; 
			}
			a++;
		}
		// isometric(map -> map, map -> row, map -> column);
	}
	if (button == SCROLL_DOWN)
	{
		ft_printf("I am scrolling down\n");
	}
	return (0);
}
