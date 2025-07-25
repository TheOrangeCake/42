/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:06:25 by masase            #+#    #+#             */
/*   Updated: 2025/07/17 15:29:11 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	save_camera(char *line, t_params *params)
{
	int	i;

	i = 0;
	if (params->quantity.camera > 0)
		return (ft_error("I can only handle one camera :("));
	while (ft_isalpha(line[i]) && line[i])
		i++;
	while (ft_isspace(line[i]) && line[i])
		i++;
	if (cam_view_point(line, &i, &params->camera) == false)
		return (false);
	while (ft_isspace(line[i]) && line[i])
		i++;
	if (cam_vector(line, &i, &params->camera) == false)
		return (false);
	while (ft_isspace(line[i]) && line[i])
		i++;
	if (save_fov(line, &i, &params->camera) == false)
		return (false);
	skip_space(line, &i);
	if (ft_isprint(line[i]))
		return (ft_error("Too much arguments for the camera parameters"));
	params->quantity.camera++;
	return (true);
}

bool	save_fov(char *line, int *i, t_camera *camera)
{
	camera->fov = atoi(line + (*i));
	if (camera->fov < 0 || camera->fov > 180)
	{
		return (ft_error("FOV can be set from 0 to 180"));
	}
	while (ft_isdigit(line[*i]))
		(*i)++;
	return (true);
}

bool	cam_view_point(char *line, int *i, t_camera *camera)
{
	if (put_position(i, &camera->pos.x, line) == false)
		return (false);
	if (put_position(i, &camera->pos.y, line) == false)
		return (false);
	if (put_position(i, &camera->pos.z, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the position parameters"));
	return (true);
}

bool	cam_vector(char *line, int *i, t_camera *camera)
{
	if (put_vector(i, &camera->vector.a, line) == false)
		return (false);
	if (put_vector(i, &camera->vector.b, line) == false)
		return (false);
	if (put_vector(i, &camera->vector.c, line) == false)
		return (false);
	if (!ft_isspace(line[*i]))
		return (ft_error("Too much arguments for the vector parameters"));
	return (true);
}
