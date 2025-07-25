/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_ambiance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:06:32 by masase            #+#    #+#             */
/*   Updated: 2025/07/17 17:48:11 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	save_ambiant(char *line, t_params *params)
{
	int	i;

	i = 0;
	if (params->quantity.ambiant > 0)
		return (ft_error("I can only handle one ambient light :("));
	while (ft_isalpha(line[i]) && line[i])
		i++;
	while (ft_isspace(line[i]) && line[i])
		i++;
	if (amb_ratio(line, &i, &params->ambient) == false)
		return (false);
	while (ft_isspace(line[i]) && line[i])
		i++;
	if (amb_rgb(line, &i, &params->ambient) == false)
		return (false);
	skip_space(line, &i);
	if (ft_isprint(line[i]))
		return (ft_error("Too much arguments for the ambiant parameters"));
	params->quantity.ambiant++;
	return (true);
}

bool	amb_ratio(char *line, int *i, t_ambient *ambient)
{
	if ((line[*i] && ft_isdigit(line[*i])) || line[*i] == '.')
		ambient->ratio = ft_atof(line + (*i));
	if (ambient->ratio < 0 || ambient->ratio > 1)
		return (ft_error("Ambient ratio can be set from 0.0 to 1.0"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("there is too much ambient ratio arguments"));
	return (true);
}

bool	amb_rgb(char *line, int *i, t_ambient *ambient)
{
	if (put_rgb(i, &ambient->color.r, line) == false)
		return (false);
	if (put_rgb(i, &ambient->color.g, line) == false)
		return (false);
	if (put_rgb(i, &ambient->color.b, line) == false)
		return (false);
	return (true);
}
