/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:49:47 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/19 11:49:58 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_map_helper(t_params *params)
{
	params -> fd = open(params -> file_name, O_RDONLY);
	params -> map = fill_map(params);
	close(params -> fd);
}

void	make_image_helper(t_params *params)
{
	params -> img = mlx_new_image(params -> mlx, WIDTH, HEIGHT);
	params -> addr = mlx_get_data_addr(params -> img, &params -> bits_per_pixel,
			&params -> line_length, &params -> endian);
	create_image(params);
	mlx_put_image_to_window(params -> mlx,
		params -> window, params -> img, 0, 0);
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	get_color(const char *line)
{
	char	*ptr;
	int		color;

	ptr = ft_strchr(line, ',');
	if (ptr == NULL)
		color = 0xffffff;
	else
		color = ft_atoi_hex(line);
	return (color);
}
