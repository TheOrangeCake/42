/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:11:45 by maw               #+#    #+#             */
/*   Updated: 2024/11/04 15:21:45 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_nod;

	new_list = NULL;
	while (lst)
	{
		new_nod = ft_lstnew(f(lst->content));
		if (!new_nod)
		{
			ft_lstclear(&new_nod, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_nod);
		lst = lst->next;
	}
	return (new_list);
}
