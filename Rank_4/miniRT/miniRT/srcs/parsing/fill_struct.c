/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:20:09 by masase            #+#    #+#             */
/*   Updated: 2025/07/10 17:31:20 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	fill_struct_2(char *line, int *i, t_params *params)
{
	if (line[*i] == 's' && line[*i + 1] == 'p'
		&& ft_isspace(line[*i + 2]))
		return (save_sphere(line, params));
	else if (line[*i] == 'p' && line[*i + 1] == 'l'
		&& ft_isspace(line[*i + 2]))
		return (save_plane(line, params));
	else if (line[*i] == 'c' && line[*i + 1] == 'y'
		&& ft_isspace(line[*i + 2]))
		return (save_cylinder(line, params));
	else if (line[*i] == 'c' && line[*i + 1] == 'o'
		&& ft_isspace(line[*i + 2]))
		return (save_cone(line, params));
	else if (line[*i] == '\n' || line[*i] == '\0')
		return (true);
	else
		return (ft_error("Unknow identifiers"));
	return (true);
}

bool	fill_struct(char *line, t_params *params)
{
	int	i;

	i = 0;
	if (line[i])
	{
		skip_space(line, &i);
		if (line[i] == 'A' && ft_isspace(line[i + 1]))
			return (save_ambiant(line, params));
		else if (line[i] == 'C' && ft_isspace(line[i + 1]))
			return (save_camera(line, params));
		else if (line[i] == 'L' && ft_isspace(line[i + 1]))
			return (save_light(line, params));
		else if (fill_struct_2(line, &i, params) == false)
			return (false);
		else
			return (true);
	}
	return (false);
}
