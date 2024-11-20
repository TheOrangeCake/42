/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:56:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/20 15:51:30 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_point	**map;
	int		fd;
	int		row;
	int		column;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Let's go FdF");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	row = 1;
	column = 0;
	fd = open("test.fdf", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Can't open file");
		exit(EXIT_FAILURE);
	}
	map = start_map(fd, &row, &column);
	if (map == NULL)
	{
		ft_printf("Map problem");
		close(fd);
		exit(EXIT_FAILURE);
	}
	fd = open("test.fdf", O_RDONLY);
	map = fill_map(map, fd, &row, &column);
	close(fd);
	isometric(map, row, column);
	create_image(&img, map, &row, &column);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
