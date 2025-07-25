/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:21:26 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/10 16:53:41 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	free_light(t_params *params)
{
	int	i;

	i = -1;
	if (!params->light)
		return ;
	while (params->light[++i])
		free(params->light[i]);
	free(params->light);
}

void	free_plane(t_params *params)
{
	int	i;

	i = -1;
	if (!params->plane)
		return ;
	while (params->plane[++i])
		free(params->plane[i]);
	free(params->plane);
}

void	free_cylinder(t_params *params)
{
	int	i;

	i = -1;
	if (!params->cylinder)
		return ;
	while (params->cylinder[++i])
		free(params->cylinder[i]);
	free(params->cylinder);
}

void	free_sphere(t_params *params)
{
	int	i;

	i = -1;
	if (!params->sphere)
		return ;
	while (params->sphere[++i])
		free(params->sphere[i]);
	free(params->sphere);
}

void	free_all(t_params *params)
{
	free_light(params);
	free_plane(params);
	free_cylinder(params);
	free_sphere(params);
	free_cone(params);
}
