/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:56:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/14 13:46:11 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

int	ft_strlen_no_color(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		i++;
		if(line[i] == ',')
			count++;
	}
	i = i - (count *9);
	ft_printf("i: %d\n", i);
	ft_printf("count: %d\n", count);
	return (i);
}

int	**initiate_2D_map(int x, int y)
{
	int	**map;
	int	i;

	map = malloc(sizeof(int *) * x );
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < x)
	{
		map[i] = malloc(sizeof(int) * y);
		if (map[i] == NULL)
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			return (NULL);
		}
	}
	return (map);
}

int	**map_check(int fd)
{
	char	*line;
	int		i;
	int		j;
	int		count;

	line = get_next_line(fd);
	if (line == NULL)
	{
		ft_printf("File is empty or error");
		exit(EXIT_FAILURE);
	}
	i = ft_strlen_no_color(line);
	count = 1;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return(initiate_2D_map(count, i)); //fix this! strlen runs on NULL
		j = ft_strlen_no_color(line);
		if (j != i)
		{
			ft_printf("Map error");
			exit(EXIT_FAILURE);
		}
		count++;
	}
	return(initiate_2D_map(count, i));
}

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		**map;
	int		fd;
	

		fd = open("pyramide.fdf", O_RDONLY);
		{
			if (fd < 0)
			{
				ft_printf("Can't open file");
				exit(EXIT_FAILURE);
			}
		}
		map = map_check(fd);
		if (map == NULL)
		{
			ft_printf("malloc map fail");
		}
		// mlx = mlx_init();
		// mlx_win = mlx_new_window(mlx, 1920, 1080, "This is a test for FdF");
		// img.img = mlx_new_image(mlx, 1920, 1080);
		// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
		// mlx_put_image_to_window(mlx, mlx_win, img.img, 100, 50);
		
		// mlx_loop(mlx);
		close (fd);
	return (0);
}
