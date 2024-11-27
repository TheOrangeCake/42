/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:42:06 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 12:55:08 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_map *map)
{
	if (keycode == ESC_KEY)
		close_window(map);
	return (0);
}

int	x_close_window(int x11_event, t_map *map)
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

int	mouse_scroll(int button, int x, int y, t_map *map)
{
	int	a;
	int	b;

	if (button == SCROLL_UP)
	{
		a = 0;
		ft_printf("I am scrolling up\n");
		ft_printf("old x: %d\n", map -> map[1][1].x);
		while (a < map -> row)
		{
			b = 0;
			while (y < map -> column)
			{
				map -> map[a][b].x *= 1.1;
				map -> map[a][b].y *= 1.1;
				b++; 
			}
			a++;
		}
		ft_printf("new x: %d\n", map -> map[1][1].x);
		// isometric(map -> map, map -> row, map -> column);
	}
	if (button == SCROLL_DOWN)
	{
		ft_printf("I am scrolling down\n");
	}
	return (0);
}
