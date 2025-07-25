/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 21:17:12 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/10 16:39:38 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	my_mlx_pixel_put(t_params *params, int x, int y, t_color color)
{
	char	*dest;

	if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH)
	{
		dest = params->data.addr + (x * params->data.line_length + y
				* (params->data.bits_per_pixel / 8));
		*(unsigned int *)dest = (color.r << 16 | color.g << 8 | color.b);
	}
}

void	image_display(t_params *params)
{
	params->data.img = mlx_new_image(params->mlx, WIDTH, HEIGHT);
	params->data.addr = mlx_get_data_addr(params->data.img,
			&params->data.bits_per_pixel, &params->data.line_length,
			&params->data.endian);
	render_object(params);
	mlx_put_image_to_window(params->mlx,
		params->window, params->data.img, 0, 0);
}

void	render(t_params *params)
{
	hook(params);
	initialise_bump(params);
	initialise_pattern(params);
	image_display(params);
	mlx_loop(params->mlx);
}
