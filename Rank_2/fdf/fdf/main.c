/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:56:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/19 15:15:26 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// hook list
void	hook_helper(t_params *params)
{
	mlx_hook(params -> window, 2, 1L << 0, key_press, params);
	mlx_hook(params -> window, 33, 1L << 0, x_close_window, params);
	mlx_hook(params -> window, 4, 1L << 2, mouse_scroll, params);
}

void	run(char *av)
{
	t_params	params;

	params.file_name = av;
	params.s_x = 1;
	params.s_y = 1;
	params.s_z = 1;
	params.d = -(M_PI / 4);
	params.row = 1;
	params.rotate_x = 0;
	params.rotate_y = 0;
	params.rotate_z = 0;
	params.switch_x = 0;
	params.switch_y = 0;
	params.switch_z = 0;
	params.color_change = 1;
	params.column = 0;
	params = file_check(params);
	fill_map_helper(&params);
	reset_map(&params);
	params.mlx = mlx_init();
	params.window = mlx_new_window(params.mlx, WIDTH, HEIGHT, "Let's go FdF");
	hook_helper(&params);
	isometric(&params);
	make_image_helper(&params);
	mlx_loop(params.mlx);
}

int	main(int ac, char *av[])
{
	if (ac == 2)
		run(av[1]);
	else if (ac == 1)
		ft_printf("Remember to insert file name");
	else
		ft_printf("Too many files");
	return (0);
}
