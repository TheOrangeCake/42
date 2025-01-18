/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:05:13 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/17 17:47:25 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	input_check_helper(char *av[])
{
	int	i;
	int	j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		if (((av[i][j] == '-' || av[i][j] == '+' || av[i][j] == ' ')
			&& av[i][j + 1] == '\0') || av[i][j] == '\0')
			return (1);
		if (av[i][j] == '-' || av[i][j] == '+')
			j++;
		while (av[i][j] != '\0')
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1[i] == '-' && s2[j] == '-')
	{
		i++;
		j++;
	}
	while (s1[i] == '+' || s1[i] == ' ' || s1[i] == '0')
		i++;
	while (s2[j] == '+' || s2[j] == ' ' || s2[j] == '0')
		j++;
	while (s1[i] != '\0' || s2[j] != '\0')
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
			return (1);
	}
	return (0);
}

t_pile	*lstnew(void *content)
{
	t_pile	*new;

	new = malloc(sizeof(t_pile));
	if (new == NULL)
		return (NULL);
	new->numb = ft_atoi(content);
	new->next = NULL;
	if (new->numb > 2147483647 || new->numb < -2147483648)
		return (NULL);
	return (new);
}

void	lstadd_back(t_pile **lst, t_pile *new)
{
	t_pile	*temp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	lstclear(t_pile **lst)
{
	t_pile	*temp;

	if (*lst != NULL && lst != NULL)
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			free(*lst);
			*lst = temp;
		}
		*lst = NULL;
	}
}

	// int	lstsize(t_pile **lst)
	// {
	// 	int		i;
	// 	t_pile	*temp;

	// 	i = 0;
	// 	temp = *lst;
	// 	while (temp != NULL)
	// 	{
	// 		i++;
	// 		temp = temp->next;
	// 	}
	// 	return (i);
	// }