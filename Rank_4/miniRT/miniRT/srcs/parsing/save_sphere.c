/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:22:36 by maw               #+#    #+#             */
/*   Updated: 2025/07/11 16:22:56 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	save_sphere_2(char *line, int *i, int j, t_params *params)
{
	if (sphere_rgb(line, i, params->sphere[j]) == false)
		return (false);
	skip_space(line, i);
	if (save_shine(i, &params->sphere[j]->shine, line) == false)
		return (false);
	skip_space(line, i);
	if (save_texture(i, &params->sphere[j]->texture_type, line) == false)
		return (false);
	skip_space(line, i);
	if (ft_isprint(line[*i]))
		return (ft_error("Too much arguments for the sphere parameters"));
	return (true);
}

bool	save_sphere(char *line, t_params *params)
{
	int	i;
	int	j;

	j = params->quantity.sphere;
	params->sphere = alloc_tab(params, SPHERE);
	params->sphere[j] = malloc (sizeof(t_sphere));
	params->sphere[j + 1] = NULL;
	i = 0;
	skip_alpha(line, &i);
	skip_space(line, &i);
	if (sphere_view_point(line, &i, params->sphere[j]) == false)
		return (false);
	skip_space(line, &i);
	if (sphere_diameter(line, &i, params->sphere[j]) == false)
		return (false);
	skip_space(line, &i);
	if (save_sphere_2(line, &i, j, params) == false)
		return (false);
	return (true);
}

bool	sphere_diameter(char *line, int *i, t_sphere *sphere)
{
	sphere->d = atof(line + (*i));
	if (sphere->d <= 0)
		return (ft_error("Sphere diameter have to be a number bigger than 0"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("there is too much sphere diameter arguments"));
	return (true);
}

bool	sphere_view_point(char *line, int *i, t_sphere *sphere)
{
	if (put_position(i, &sphere->pos.x, line) == false)
		return (false);
	if (put_position(i, &sphere->pos.y, line) == false)
		return (false);
	if (put_position(i, &sphere->pos.z, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the position parameters"));
	return (true);
}

bool	sphere_rgb(char *line, int *i, t_sphere *sphere)
{
	if (put_rgb(i, &sphere->color.r, line) == false)
		return (false);
	if (put_rgb(i, &sphere->color.g, line) == false)
		return (false);
	if (put_rgb(i, &sphere->color.b, line) == false)
		return (false);
	return (true);
}
