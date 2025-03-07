/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:55:10 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/07 17:03:27 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	free_split(char **list)
{
	int	i;

	i = 0;
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
}

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

char	**transform(char **av)
{
	int		i;
	int		j;
	int		count;
	char	**split;

	i = 0;
	count = 0;
	while (av[i] != NULL)
	{
		split = ft_split(av[i], ' ');
		if (split == NULL)
			return (NULL);
		j = 0;
		while (split[j++] != NULL)
			count++;
		free_split(split);
		i++;
	}
	split = transform_next(av, split, count);
	return (split);
}

t_pile	**run(t_pile **a, int ac, char **av)
{
	if (input_check(av) == 1)
		return (NULL);
	else
		a = initiate_a(av, a);
	if (a == NULL)
		return (NULL);
	a = checker(a);
	if (a == NULL)
		return (NULL);
	return (a);
}
