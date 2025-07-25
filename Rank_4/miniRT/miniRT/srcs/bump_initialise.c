/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_initialise.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:32:50 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/09 17:16:25 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	free_maps(t_params *params)
{
	if (params->bump.earth)
		mlx_destroy_image(params->mlx, params->bump.earth);
	if (params->bump.earthbump)
		mlx_destroy_image(params->mlx, params->bump.earthbump);
	if (params->bump.mars)
		mlx_destroy_image(params->mlx, params->bump.mars);
	if (params->bump.marsbump)
		mlx_destroy_image(params->mlx, params->bump.marsbump);
	if (params->bump.mercu)
		mlx_destroy_image(params->mlx, params->bump.mercu);
	if (params->bump.mercubump)
		mlx_destroy_image(params->mlx, params->bump.mercubump);
	if (params->bump.pluto)
		mlx_destroy_image(params->mlx, params->bump.pluto);
	if (params->bump.plutobump)
		mlx_destroy_image(params->mlx, params->bump.plutobump);
	if (params->bump.venus)
		mlx_destroy_image(params->mlx, params->bump.venus);
	if (params->bump.venusbump)
		mlx_destroy_image(params->mlx, params->bump.venusbump);
}

void	free_bump(t_params *params)
{
	free_maps(params);
	free_all(params);
	mlx_destroy_window(params->mlx, params->window);
	mlx_destroy_display(params->mlx);
	free(params->mlx);
	printf("Texture or bump map error\n");
	exit (1);
}

void	initialise_more_bump(t_params *params, int height, int width)
{
	params->bump.mercu = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/mercury.xpm", &width, &height);
	if (!params->bump.mercu)
		free_bump(params);
	params->bump.mercubump = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/mercurybump.xpm", &width, &height);
	if (!params->bump.mercubump)
		free_bump(params);
	params->bump.pluto = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/pluto.xpm", &width, &height);
	if (!params->bump.pluto)
		free_bump(params);
	params->bump.plutobump = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/plutobump.xpm", &width, &height);
	if (!params->bump.plutobump)
		free_bump(params);
	params->bump.venus = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/venus.xpm", &width, &height);
	if (!params->bump.venus)
		free_bump(params);
	params->bump.venusbump = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/venusbump.xpm", &width, &height);
	if (!params->bump.venusbump)
		free_bump(params);
}

void	initialise_bump(t_params *params)
{
	int	height;
	int	width;

	height = XPM_HEIGHT;
	width = XPM_WIDTH;
	params->bump.earth = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/earth.xpm", &width, &height);
	if (!params->bump.earth)
		free_bump(params);
	params->bump.earthbump = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/earthbump.xpm", &width, &height);
	if (!params->bump.earthbump)
		free_bump(params);
	params->bump.mars = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/mars.xpm", &width, &height);
	if (!params->bump.mars)
		free_bump(params);
	params->bump.marsbump = mlx_xpm_file_to_image(params->mlx,
			"./srcs/maps/marsbump.xpm", &width, &height);
	if (!params->bump.marsbump)
		free_bump(params);
	initialise_more_bump(params, height, width);
}
