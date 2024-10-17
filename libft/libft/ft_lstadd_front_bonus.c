/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:20:05 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/13 15:20:05 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
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
// 	ft_lstadd_front(&head, test1);
// 	while (head)
// 	{
// 		temp = head->next;
// 		printf("First: %s\n", (char *)head->content);
// 		head = temp;
// 	}
// 	while (head)
// 	{
// 		temp = head->next;
// 		free(head);
// 		head = temp;
// 	}
// 	return (0);
// }