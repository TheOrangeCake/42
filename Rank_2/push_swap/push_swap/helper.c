/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:05:13 by hoannguy          #+#    #+#             */
/*   Updated: 2024/12/04 14:49:48 by hoannguy         ###   ########.fr       */
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

t_pile	*ft_lstnew(void *content)
{
	t_pile	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->number = ft_atoi(content);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_pile **lst, t_pile *new)
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

void	ft_lstadd_front(t_pile **lst, t_pile *new)
{
	new->next = *lst;
	*lst = new;
}

// void	del(void *content)
// {
// 	free(content);
// }

// void	ft_lstdelone(t_list *lst, void (*del)(void*))
// {
// 	if (lst != NULL && del != NULL)
// 	{
// 		del(lst->content);
// 		free(lst);
// 	}
// }

// void	ft_lstclear(t_pile **lst, void (*del)(void *))
// {
// 	t_pile	*temp;

// 	if (*lst != NULL && lst != NULL && del != NULL)
// 	{
// 		while (*lst != NULL)
// 		{
// 			temp = (*lst)->next;
// 			ft_lstdelone(*lst, del);
// 			*lst = temp;
// 		}
// 	}
// }
