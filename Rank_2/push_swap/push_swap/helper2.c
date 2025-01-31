/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:24:18 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/31 19:53:50 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	sorted_a(t_pile **a)
{
	t_pile	*temp;
	int		i;

	temp = *a;
	i = temp->numb;
	temp = temp->next;
	while (temp != NULL)
	{
		if (i > temp->numb)
			return (1);
		i = temp->numb;
		temp = temp->next;
	}
	return (0);
}

int	input_check(char *av[])
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && (av[i][j] != ' '
					&& av[i][j] != '-' && av[i][j] != '+'))
				return (1);
			j++;
		}
		j = i + 1;
		while (av[j] != NULL)
		{
			if (ft_strcmp(av[i], av[j++]) == 0)
				return (1);
		}
		i++;
	}
	if (input_check_helper(av) == 1 || check_0(av) == 1)
		return (1);
	return (0);
}

t_pile	**initiate_a(char *av[], t_pile **a)
{
	t_pile	*node;
	int		i;

	i = 1;
	while (av[i] != NULL)
	{
		node = lstnew(av[i]);
		if (node == NULL)
			return (lstclear(a), NULL);
		lstadd_back(a, node);
		i++;
	}
	return (a);
}

int	check_0(char *av[])
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (av[i] != NULL)
	{
		if (j == 0 && ft_atoi(av[i]) == 0)
			return (1);
		else if (ft_atoi(av[i]) == 0)
			j = 0;
		i++;
	}
	return (0);
}
