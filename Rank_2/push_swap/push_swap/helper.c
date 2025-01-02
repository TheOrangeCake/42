/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:05:13 by hoannguy          #+#    #+#             */
/*   Updated: 2025/01/02 22:29:41 by hoannguy         ###   ########.fr       */
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
