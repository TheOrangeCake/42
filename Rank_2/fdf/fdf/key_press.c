/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:55:57 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 12:43:51 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_window(t_map *map)
{
	while (map -> row > 0)
	{
		free((map -> map)[map -> row - 1]);
		map -> row--;
	}
	free(map -> map);
	ft_printf("Program terminated\n");
	exit(0);
}

// void	projection(t_map map)
// {
// 	isometric(map);
// }