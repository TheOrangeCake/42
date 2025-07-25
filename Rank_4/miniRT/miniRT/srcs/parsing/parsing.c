/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:15:47 by masase            #+#    #+#             */
/*   Updated: 2025/07/10 18:01:55 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

bool	free_close_fd(char *line, int fd)
{
	free(line);
	get_next_line(-1);
	close(fd);
	return (false);
}

bool	read_scene(char *file, t_params *params)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_error("cant' open the file"));
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line)
		{
			if (fill_struct(line, params) == true)
				free(line);
			else
				return (free_close_fd(line, fd));
		}
	}
	close(fd);
	return (true);
}

bool	check_arg(char *str)
{
	int	len;

	if (!str)
		return (false);
	len = ft_strlen(str);
	if (ft_strncmp(str + (len - 3), ".rt", 3) == 0)
		return (true);
	return (false);
}

bool	parsing(char *file, t_params *params)
{
	if (check_arg(file) == false)
		return (ft_error("file must finish by .rt"));
	if (read_scene(file, params) == false)
		return (false);
	return (true);
}
