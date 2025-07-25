/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:40:50 by maw               #+#    #+#             */
/*   Updated: 2025/07/17 17:36:54 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	save_cylinder_2(char *line, int *i, int j, t_params *params)
{
	if (cylinder_height(line, i, params->cylinder[j]) == false)
		return (false);
	skip_space(line, i);
	if (cylinder_rgb(line, i, params->cylinder[j]) == false)
		return (false);
	skip_space(line, i);
	if (save_shine(i, &params->cylinder[j]->shine, line) == false)
		return (false);
	skip_space(line, i);
	if (save_texture(i, &params->cylinder[j]->texture_type, line) == false)
		return (false);
	skip_space(line, i);
	if (ft_isprint(line[*i]))
		return (ft_error("Too much arguments for the cylinder parameters"));
	return (true);
}

bool	save_cylinder(char *line, t_params *params)
{
	int	i;
	int	j;

	i = 0;
	j = params->quantity.cylinder;
	params->cylinder = alloc_tab(params, CYLINDER);
	params->cylinder[j] = malloc (sizeof(t_cylinder));
	params->cylinder[j + 1] = NULL;
	skip_alpha(line, &i);
	skip_space(line, &i);
	if (cylinder_view_point(line, &i, params->cylinder[j]) == false)
		return (false);
	skip_space(line, &i);
	if (cylinder_vector(line, &i, params->cylinder[j]) == false)
		return (false);
	skip_space(line, &i);
	if (cylinder_diameter(line, &i, params->cylinder[j]) == false)
		return (false);
	skip_space(line, &i);
	if (save_cylinder_2(line, &i, j, params) == false)
		return (false);
	return (true);
}
