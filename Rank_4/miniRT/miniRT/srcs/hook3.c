/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:31:10 by hoannguy          #+#    #+#             */
/*   Updated: 2025/06/15 14:25:41 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	camera_pos_backward(t_params *params)
{
	params->camera.pos.z -= 1;
	mlx_destroy_image(params->mlx, params->data.img);
	render(params);
}

void	camera_look_up(t_params *params)
{
	params->camera.vector.b += 0.1;
	mlx_destroy_image(params->mlx, params->data.img);
	render(params);
}

void	camera_look_down(t_params *params)
{
	params->camera.vector.b -= 0.1;
	mlx_destroy_image(params->mlx, params->data.img);
	render(params);
}

void	camera_look_left(t_params *params)
{
	params->camera.vector.a -= 0.1;
	mlx_destroy_image(params->mlx, params->data.img);
	render(params);
}

void	camera_look_right(t_params *params)
{
	params->camera.vector.a += 0.1;
	mlx_destroy_image(params->mlx, params->data.img);
	render(params);
}
