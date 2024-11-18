/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:38:16 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/18 14:10:14 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include "libft.h"
#include "mlx.h"

# define ABS(Value) (Value * ((Value > 0) - (Value < 0)))

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_point
{
	int				z;
	unsigned long	color;
	int			end;
}	t_point;

t_point	**start_map(int fd, int *row, int *column);
t_point	**fill_map(t_point **map, int fd, int *row);
void    create_image(t_data *img, t_point **map);

#endif
