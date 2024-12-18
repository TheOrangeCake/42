/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:56:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/18 11:11:40 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// check map validity and malloc map
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

// hook list
void	hook_helper(t_params *params)
{
	mlx_hook(params -> window, 2, 1L << 0, key_press, params);
	mlx_hook(params -> window, 33, 1L << 0, x_close_window, params);
	mlx_hook(params -> window, 4, 1L << 2, mouse_scroll, params);
}

int	main(void)
{
	t_params	params;

	params.s_x = 1;
	params.s_y = 1;
	params.s_z = 1;
	params.row = 1;
	params.column = 0;
	params = file_check(params);
	fill_map_helper(&params);
	params.mlx = mlx_init();
	params.window = mlx_new_window(params.mlx, WIDTH, HEIGHT, "Let's go FdF");
	hook_helper(&params);
	isometric(&params);
	make_image_helper(&params);
	mlx_loop(params.mlx);
	return (0);
}
