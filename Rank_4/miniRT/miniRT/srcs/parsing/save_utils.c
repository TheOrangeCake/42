/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:54:55 by masase            #+#    #+#             */
/*   Updated: 2025/07/10 19:00:14 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	save_texture(int *i, int *value, char *line)
{
	if (line[*i] && ft_isdigit(line[*i]))
		*value = ft_atoi(line + (*i));
	else
		return (ft_error
			("Texture parameters have to be a number from 0 to 12"));
	if (*value < 0 || *value > 12)
		return (ft_error
			("Texture parameters have to be a number from 0 to 12"));
	while (ft_isdigit(line[*i]) && line[*i])
		(*i)++;
	return (true);
}

bool	save_shine(int *i, float *value, char *line)
{
	if (line[*i] && ft_isdigit(line[*i]))
		*value = ft_atof(line + (*i));
	else
		return (ft_error
			("Shine parameters have to be a number from 10 to 200"));
	if (*value < 10 || *value > 200)
		return (ft_error("Shine can set be set from 0 to 255"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	return (true);
}

bool	put_rgb(int *i, int *value, char *line)
{
	if (line[*i] && ft_isdigit(line[*i]))
	{
		*value = ft_atoi(line + (*i));
	}
	else
		return (ft_error("RGB parameters have to be a number from 0 to 255"));
	if (*value < 0 || *value > 255)
		return (ft_error("RGB can set be set from 0 to 255"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (line[*i] == ',')
		(*i)++;
	return (true);
}

bool	put_vector(int *i, float *value, char *line)
{
	if (line[*i] && ft_isdigit_point(line[*i]))
	{
		*value = ft_atof(line + (*i));
	}
	else
		return (ft_error("Vector parameters have to be a number from -1 to 1"));
	if (*value < -1 || *value > 1)
		return (ft_error("Vector can be set from -1 to 1"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (line[*i] == ',')
		(*i)++;
	return (true);
}

bool	put_position(int *i, float *value, char *line)
{
	if (line[*i] && ft_isdigit_point(line[*i]))
	{
		*value = ft_atof(line + (*i));
	}
	else
		return (ft_error("Position parameters have to be a number"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (line[*i] == ',')
		(*i)++;
	return (true);
}
