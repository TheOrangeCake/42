/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:14:10 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/07 16:54:10 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ac_count(char **argument)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (argument[i] != NULL)
	{
		count++;
		i++;
	}
	return (count);
}

char	**transform_next(char **av, char **split, int count)
{
	t_saveline	save;

	save.i = 0;
	save.k = 0;
	split = malloc(sizeof(char *) * (count + 1));
	if (split == NULL)
		return (NULL);
	while (av[save.i] != NULL)
	{
		save.temp = ft_split(av[save.i], ' ');
		if (save.temp == NULL)
			return (NULL);
		save.j = 0;
		while (save.temp[save.j] != NULL)
		{
			split[save.k] = ft_strdup(save.temp[save.j++]);
			if (split[save.k] == NULL)
				return (free_split(save.temp), NULL);
			save.k++;
		}
		free_split(save.temp);
		save.i++;
	}
	split[save.k] = NULL;
	return (split);
}
