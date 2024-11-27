/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:55:57 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 15:34:53 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	close_window(t_params *params)
{
	// while (params -> row > 0)
	// {
	// 	free((params -> map)[params -> row - 1]);
	// 	params -> row--;
	// }
	// free(params -> map);
	ft_printf("Program terminated\n");
	exit(0);
}

void	projection(t_params params)
{
	isometric(params.map, params.row, params.column);
	// military(params.map, params.row, params.column, (M_PI / 4));
}