/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cylinder_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:34 by masase            #+#    #+#             */
/*   Updated: 2025/07/10 18:59:27 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	cylinder_diameter(char *line, int *i, t_cylinder *cylinder)
{
	cylinder->d = ft_atof(line + (*i));
	if (cylinder->d <= 0)
		return (ft_error("Cylinder diameter have to be number bigger than 0"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("there is too much cylinder diameter arguments"));
	return (true);
}

bool	cylinder_height(char *line, int *i, t_cylinder *cylinder)
{
	cylinder->h = ft_atof(line + (*i));
	if (cylinder->h <= 0)
		return (ft_error("Cylinder height have to be a number bigger than 0"));
	if (skip_sign_and_number(line, i) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("there is too much cylinder height arguments"));
	return (true);
}

bool	cylinder_view_point(char *line, int *i, t_cylinder *cylinder)
{
	if (put_position(i, &cylinder->pos.x, line) == false)
		return (false);
	if (put_position(i, &cylinder->pos.y, line) == false)
		return (false);
	if (put_position(i, &cylinder->pos.z, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the position parameters"));
	return (true);
}

bool	cylinder_vector(char *line, int *i, t_cylinder *cylinder)
{
	if (put_vector(i, &cylinder->vector.a, line) == false)
		return (false);
	if (put_vector(i, &cylinder->vector.b, line) == false)
		return (false);
	if (put_vector(i, &cylinder->vector.c, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the vector parameters"));
	return (true);
}

bool	cylinder_rgb(char *line, int *i, t_cylinder *cylinder)
{
	if (put_rgb(i, &cylinder->color.r, line) == false)
		return (false);
	if (put_rgb(i, &cylinder->color.g, line) == false)
		return (false);
	if (put_rgb(i, &cylinder->color.b, line) == false)
		return (false);
	return (true);
}
