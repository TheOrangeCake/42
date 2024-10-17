/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:26:11 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/13 15:26:11 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
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

// int	main(void)
// {
// 	char	text[] = "Hello";
// 	t_list	*test;
// 	char	text1[] = "World";
// 	t_list	*test1;
// 	t_list	*head;
// 	t_list	*temp;

// 	test = ft_lstnew(text);
// 	test1 = ft_lstnew(text1);

// 	head = test;
// 	ft_lstadd_back(&head, test1);
// 	while (head)
// 	{
// 		temp = head->next;
// 		printf("%s\n", (char *)head->content);
// 		head = temp;
// 	}
// 	printf("size: %d\n", (int)ft_lstsize(test));
// 	while (head)
// 	{
// 		temp = head->next;
// 		free(head);
// 		head = temp;
// 	}
// 	return (0);
// }