/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:20:02 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/16 20:19:32 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// put pixel to screen
void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

void    create_image(t_data *data, int *row, int *column)
{
    int x;
    int y;
    int i;
    int j;

    j = 0;
    x = 0;
    while (j < *column)
    {
        i = 0;
        y = 0;
        while (i < *row)
        {
            my_mlx_pixel_put(data, x, y, 0x00ffffff);
            i++;
            y += 100;
        }
        x += 100;
        j++;
    }
}