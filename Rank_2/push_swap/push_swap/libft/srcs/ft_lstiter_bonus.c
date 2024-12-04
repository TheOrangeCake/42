/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:27:48 by hoannguy          #+#    #+#             */
/*   Updated: 2024/10/16 22:27:48 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst != NULL && f != NULL)
	{
		while (lst != NULL)
		{
			(*f)(lst->content);
			lst = lst->next;
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

// void	change(void *content)
// {
// 	int	i;
// 	char	*ptr;

// 	i = 0;
// 	ptr = (char *)content;
// 	while (ptr[i])
// 	{
// 		ptr[i] = ptr[i] + 1;
// 		i++;
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
// 	ft_lstiter(test, change);
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
