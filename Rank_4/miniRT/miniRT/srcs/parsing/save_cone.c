/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:51:53 by masase            #+#    #+#             */
/*   Updated: 2025/07/17 17:48:57 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	save_cone_2(char *line, int *i, int j, t_params *params)
{
	if (cone_height(line, i, params->cone[j]) == false)
		return (false);
	skip_space(line, i);
	if (cone_rgb(line, i, params->cone[j]) == false)
		return (false);
	skip_space(line, i);
	if (save_shine(i, &params->cone[j]->shine, line) == false)
		return (false);
	skip_space(line, i);
	if (save_texture(i, &params->cone[j]->texture_type, line) == false)
		return (false);
	skip_space(line, i);
	if (ft_isprint(line[*i]))
		return (ft_error("Too much arguments for the cone parameters"));
	return (true);
}

bool	save_cone(char *line, t_params *params)
{
	int	i;
	int	j;

	i = 0;
	j = params->quantity.cone;
	params->cone = alloc_tab(params, CONE);
	params->cone[j] = malloc (sizeof(t_cone));
	params->cone[j + 1] = NULL;
	while (ft_isalpha(line[i]) && line[i])
		i++;
	skip_space(line, &i);
	if (cone_view_point(line, &i, params->cone[j]) == false)
		return (false);
	skip_space(line, &i);
	if (cone_vector(line, &i, params->cone[j]) == false)
		return (false);
	skip_space(line, &i);
	if (cone_diameter(line, &i, params->cone[j]) == false)
		return (false);
	skip_space(line, &i);
	if (save_cone_2(line, &i, j, params) == false)
		return (false);
	return (true);
}
