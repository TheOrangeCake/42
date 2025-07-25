/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:47:20 by maw               #+#    #+#             */
/*   Updated: 2025/07/17 17:49:11 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	save_light(char *line, t_params *params)
{
	int	i;
	int	j;

	j = params->quantity.light;
	params->light = alloc_tab(params, LIGHT);
	params->light[j] = malloc (sizeof(t_light));
	params->light[j + 1] = NULL;
	i = 0;
	while (ft_isalpha(line[i]) && line[i])
		i++;
	skip_space(line, &i);
	if (light_view_point(line, &i, params->light[j]) == false)
		return (false);
	skip_space(line, &i);
	if (light_ratio(line, &i, params->light[j]) == false)
		return (false);
	skip_space(line, &i);
	if (light_rgb(line, &i, params->light[j]) == false)
		return (false);
	skip_space(line, &i);
	if (ft_isprint(line[i]))
		return (ft_error("Too much arguments for the light parameters"));
	return (true);
}

bool	light_ratio(char *line, int *i, t_light *light)
{
	light->ratio = atof(line + (*i));
	if (light->ratio < 0 || light->ratio > 1)
		return (ft_error
			("Light ratio have to be a number set from 0.0 to 1.0"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("there is too much light ratio arguments"));
	return (true);
}

bool	light_view_point(char *line, int *i, t_light *light)
{
	if (put_position(i, &light->pos.x, line) == false)
		return (false);
	if (put_position(i, &light->pos.y, line) == false)
		return (false);
	if (put_position(i, &light->pos.z, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the position parameters"));
	return (true);
}

bool	light_rgb(char *line, int *i, t_light *light)
{
	if (put_rgb(i, &light->color.r, line) == false)
		return (false);
	if (put_rgb(i, &light->color.g, line) == false)
		return (false);
	if (put_rgb(i, &light->color.b, line) == false)
		return (false);
	return (true);
}
