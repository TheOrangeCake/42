/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:05:40 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/16 14:14:44 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int **fill_map(int **map, int fd, int *i)
{
    char    *line;
    char    **array;
    int     x;
    int     y;

    x = 0;
    while(x <= *i)
    {
        line = get_next_line(fd);
        array = ft_split(line, ' ');
        ft_printf("i: %d\n", *i);
        y = 0;
        // while (!array[y])
        // {
        //     map[x][y] = ft_atoi(array[y]);
        //     y++;
        // }
        x++;
    }
    return (map);
}
