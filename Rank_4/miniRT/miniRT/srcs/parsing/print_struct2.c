/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:02:49 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/11 17:02:58 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	print_camera_as_array(t_camera *cam)
{
	printf("Camera\n");
	printf("Position: [%.2f, %.2f, %.2f]\n",
		cam->pos.x, cam->pos.y, cam->pos.z);
	printf("Orientation: [%.2f, %.2f, %.2f]\n",
		cam->vector.a, cam->vector.b, cam->vector.c);
	printf("Field of View: %d\n", cam->fov);
}
