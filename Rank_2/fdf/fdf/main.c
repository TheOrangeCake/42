/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:56:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/18 15:05:33 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_point		**map;
	int		fd;
	int		row;
	
	row = 0;
	fd = open("test.fdf", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Can't open file");
		exit(EXIT_FAILURE);
	}
	map = start_map(fd, &row);
	if (map == NULL)
	{
		ft_printf("fail to read file");
		close(fd);
		exit(EXIT_FAILURE);
	}
	fd = open("test.fdf", O_RDONLY);
	map = fill_map(map, fd, &row);
	close(fd);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Let's go FdF");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	create_image(&img, map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 100, 100);
		
	mlx_loop(mlx);
	return (0);
}
