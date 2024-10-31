/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:05:59 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/17 13:41:05 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (*lst != NULL && lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp;
		}
	}
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

// int	main(void)
// {
// 	char	*text = strdup("Hello");
// 	t_list	*test;
// 	char	*text1 = strdup("World");
// 	t_list	*test1;
// 	char	*text2 = strdup("Cat");
// 	t_list	*test2;
// 	t_list	*head;
// 	t_list	*temp;

// 	test = ft_lstnew(text);
// 	test1 = ft_lstnew(text1);
// 	test2 = ft_lstnew(text2);

// 	head = test;
// 	ft_lstadd_back(&head, test1);
// 	ft_lstadd_back(&head, test2);
// 	ft_lstclear(&head, del);
// 	if (head == NULL)
// 		printf("NULL\n");
// 	while (head)
// 	{
// 		printf("%s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	while (head)
// 	{
// 		temp = head->next;
// 		free(head);
// 		head = temp;
// 	}
// 	return (0);
// }
