/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:56:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/16 14:09:48 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		**map;
	int		fd;
	int		x;
	
	x = 0;
	fd = open("pyramide.fdf", O_RDONLY);
	{
		if (fd < 0)
		{
			ft_printf("Can't open file");
			exit(EXIT_FAILURE);
		}
	}
	map = check_map(fd, &x);
	if (map == NULL)
	{
		ft_printf("malloc map fail");
	}
	map = fill_map(map, fd, &x);
		// mlx = mlx_init();
		// mlx_win = mlx_new_window(mlx, 1920, 1080, "This is a test for FdF");
		// img.img = mlx_new_image(mlx, 1920, 1080);
		// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
		// mlx_put_image_to_window(mlx, mlx_win, img.img, 100, 50);
		
		// mlx_loop(mlx);
	close (fd);
	return (0);
}
