/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:56:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/16 20:16:45 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		**map;
	int		fd;
	int		row;
	int		column;
	
	row = 0;
	fd = open("test.fdf", O_RDONLY);
	{
		if (fd < 0)
		{
			ft_printf("Can't open file");
			exit(EXIT_FAILURE);
		}
	}
	map = check_map(fd, &row, &column);
	if (map == NULL)
	{
		ft_printf("malloc map fail");
	}
	close(fd);
	fd = open("test.fdf", O_RDONLY);
	map = fill_map(map, fd, &row);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Let's go FdF");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	printf("row: %d\n", row);
	printf("column: %d\n", column);
	create_image(&img, &row, &column);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 500, 500);
		
	mlx_loop(mlx);
	close(fd);
	return (0);
}
