/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:56:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/27 16:12:06 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_map_helper(t_params *params)
{
	params -> fd = open("test.fdf", O_RDONLY);
	params -> map = fill_map(params -> map, params -> fd, &(params -> row), &(params -> column));
	close(params -> fd);
}

t_params	file_check(t_params params)
{
	params.fd = open("test.fdf", O_RDONLY);
	if (params.fd < 0)
	{
		ft_printf("Can't open file");
		close(params.fd);
		exit(EXIT_FAILURE);
	}
	params.map = start_map(params.fd, &(params.row), &(params.column));
	if (params.map == NULL)
	{
		ft_printf("Map error");
		close(params.fd);
		exit(EXIT_FAILURE);
	}
	close (params.fd);
	return (params);
}

void	hook_helper(t_params *params)
{
	mlx_hook(params -> window, 2, 1L << 0, key_press, params);
	mlx_hook(params -> window, 33, 1L << 0, x_close_window, params);
	mlx_hook(params -> window, 4, 1L << 2, mouse_scroll, params);
}

int	main(void)
{
	t_params params;

	params.row = 1;
	params.column = 0;
	params = file_check(params);
	fill_map_helper(&params);
	params.mlx = mlx_init();
	params.window = mlx_new_window(params.mlx, WIDTH, HEIGHT, "Let's go FdF");
	params.img = mlx_new_image(params.mlx, WIDTH, HEIGHT);
	params.addr = mlx_get_data_addr(params.img, &params.bits_per_pixel,
			&params.line_length, &params.endian);
	hook_helper(&params);
	isometric(params.map, params.row, params.column);
	create_image(&params);
	mlx_put_image_to_window(params.mlx, params.window, params.img, 0, 0);
	mlx_loop(params.mlx);
	return (0);
}
