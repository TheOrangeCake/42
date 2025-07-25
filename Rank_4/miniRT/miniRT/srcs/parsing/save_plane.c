/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:46:44 by maw               #+#    #+#             */
/*   Updated: 2025/07/17 17:48:23 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	save_plane(char *line, t_params *params)
{
	int	i;
	int	j;

	j = params->quantity.plane;
	params->plane = alloc_tab(params, PLANE);
	params->plane[j] = malloc (sizeof(t_plane));
	params->plane[j + 1] = NULL;
	i = 0;
	skip_alpha(line, &i);
	skip_space(line, &i);
	if (plane_view_point(line, &i, params->plane[j]) == false)
		return (false);
	skip_space(line, &i);
	if (plane_vector(line, &i, params->plane[j]) == false)
		return (false);
	skip_space(line, &i);
	if (plane_rgb(line, &i, params->plane[j]) == false)
		return (false);
	skip_space(line, &i);
	if (save_texture(&i, &params->plane[j]->texture_type, line) == false)
		return (false);
	skip_space(line, &i);
	if (ft_isprint(line[i]))
		return (ft_error("Too much arguments for the plane parameters"));
	return (true);
}

bool	plane_view_point(char *line, int *i, t_plane *plane)
{
	if (put_position(i, &plane->pos.x, line) == false)
		return (false);
	if (put_position(i, &plane->pos.y, line) == false)
		return (false);
	if (put_position(i, &plane->pos.z, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the position parameters"));
	return (true);
}

bool	plane_vector(char *line, int *i, t_plane *plane)
{
	if (put_vector(i, &plane->vector.a, line) == false)
		return (false);
	if (put_vector(i, &plane->vector.b, line) == false)
		return (false);
	if (put_vector(i, &plane->vector.c, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the vector parameters"));
	return (true);
}

bool	plane_rgb(char *line, int *i, t_plane *plane)
{
	if (put_rgb(i, &plane->color.r, line) == false)
		return (false);
	if (put_rgb(i, &plane->color.g, line) == false)
		return (false);
	if (put_rgb(i, &plane->color.b, line) == false)
		return (false);
	return (true);
}
