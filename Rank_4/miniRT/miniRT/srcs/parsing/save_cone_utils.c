/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cone_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:13 by masase            #+#    #+#             */
/*   Updated: 2025/07/10 18:59:11 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	cone_diameter(char *line, int *i, t_cone *cone)
{
	cone->d = ft_atof(line + (*i));
	if (cone->d <= 0)
		return (ft_error("Cone diameter have to be number bigger than 0"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("there is too much cone diameter arguments"));
	return (true);
}

bool	cone_height(char *line, int *i, t_cone *cone)
{
	cone->h = ft_atof(line + (*i));
	if (cone->h <= 0)
		return (ft_error("Cone height have to be a number bigger than 0"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("there is too much cone height arguments"));
	return (true);
}

bool	cone_view_point(char *line, int *i, t_cone *cone)
{
	if (put_position(i, &cone->pos.x, line) == false)
		return (false);
	if (put_position(i, &cone->pos.y, line) == false)
		return (false);
	if (put_position(i, &cone->pos.z, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the position parameters"));
	return (true);
}

bool	cone_vector(char *line, int *i, t_cone *cone)
{
	if (put_vector(i, &cone->vector.a, line) == false)
		return (false);
	if (put_vector(i, &cone->vector.b, line) == false)
		return (false);
	if (put_vector(i, &cone->vector.c, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the vector parameters"));
	return (true);
}

bool	cone_rgb(char *line, int *i, t_cone *cone)
{
	if (put_rgb(i, &cone->color.r, line) == false)
		return (false);
	if (put_rgb(i, &cone->color.g, line) == false)
		return (false);
	if (put_rgb(i, &cone->color.b, line) == false)
		return (false);
	return (true);
}
