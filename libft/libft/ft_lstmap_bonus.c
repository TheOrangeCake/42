/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:13:54 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/17 13:43:26 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	temp = ft_lstnew((*f)(lst->content));
	if (temp == NULL)
		return (NULL);
	new = temp;
	lst = lst->next;
	while (lst)
	{
		temp->next = ft_lstnew((*f)(lst->content));
		if (temp->next == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (new);
}

// #include <stdio.h>
// #include <stdlib.h>

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*new;

// 	new = malloc(sizeof(t_list));
// 	if (new == NULL)
// 		return (NULL);
// 	new->content = content;
// 	new->next = NULL;
// 	return (new);
// }

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*temp;

// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		temp = *lst;
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		temp->next = new;
// 	}
// 	new->next = NULL;
// }

// void	*change(void *content)
// {
//     int		i;
//     char	*ptr;

//     i = 0;
//     ptr = strdup((char *)content);
//     if (ptr == NULL)
//         return (NULL);
//     while (ptr[i])
//     {
// 		ptr[i] = ptr[i] + 1;
//         i++;
//     }
//     return (ptr);
// }

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

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*temp;

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

// int	main(void)
// {
// 	char	*text = strdup("Hello");
// 	t_list	*test;
// 	char	*text1 = strdup("World");
// 	t_list	*test1;
// 	char	*text2 = strdup("Cat");
// 	t_list	*test2;
// 	t_list	*head;
// 	t_list	*new;
// 	t_list	*temp;

// 	test = ft_lstnew(text);
// 	test1 = ft_lstnew(text1);
// 	test2 = ft_lstnew(text2);

// 	head = test;
// 	ft_lstadd_back(&head, test1);
// 	ft_lstadd_back(&head, test2);
// 	new = ft_lstmap(head, change, del);
// 	temp = new;
// 	while (temp)
// 	{
// 		printf("%s\n", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	return (0);
// }
