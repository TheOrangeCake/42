/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 00:03:01 by hoannguy          #+#    #+#             */
/*   Updated: 2025/07/10 16:39:07 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	free_cone(t_params *params)
{
	int	i;

	i = -1;
	if (!params->cone)
		return ;
	while (params->cone[++i])
		free(params->cone[i]);
	free(params->cone);
}
