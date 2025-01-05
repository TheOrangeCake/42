/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:05:13 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/05 23:57:15 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
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
	// if (new->numb > 2147483647 || new->numb < -2147483648)
	// {
	// 	write(2, "Error\n", 6);
	// 	return (NULL);
	// }
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

int	lstsize(t_pile **lst)
{
	int		i;
	t_pile	*temp;

	i = 0;
	temp = *lst;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
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
