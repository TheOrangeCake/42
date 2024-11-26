/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:56:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/26 21:48:33 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	file_check(t_map map)
{
	int	fd;

	fd = open("test.fdf", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Can't open file");
		close(fd);
		exit(EXIT_FAILURE);
	}
	map.map = start_map(fd, &(map.row), &(map.column));
	if (map.map == NULL)
	{
		ft_printf("Map error");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close (fd);
	return (map);
}

int	main(void)
{
	t_wins	wins;
	t_data	img;
	t_map	map;
	int		fd;

	wins.mlx = mlx_init();
	wins.window = mlx_new_window(wins.mlx, WIDTH, HEIGHT, "Let's go FdF");
	img.img = mlx_new_image(wins.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	map.row = 1;
	map.column = 0;
	map = file_check(map);
	fd = open("test.fdf", O_RDONLY);
	map.map = fill_map(map.map, fd, &(map.row), &(map.column));
	close(fd);
	isometric(map.map, map.row, map.column);
	create_image(&img, map.map, &(map.row), &(map.column));
	mlx_hook(wins.window, 2, 1L << 0, close_window, &map);
	mlx_put_image_to_window(wins.mlx, wins.window, img.img, 0, 0);
	mlx_loop(wins.mlx);
	return (0);
}
