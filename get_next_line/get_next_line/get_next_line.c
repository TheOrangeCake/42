/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:43 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/01 17:48:45 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct	line
{
	char		*s;
	struct line	*next;
};

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_line(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

line	*ft_lstnew(void *content)
{
	line	*new;

	new = malloc(sizeof(line));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(line **lst, line *new)
{
	line	*temp;

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

int	hold_check(char *hold)
{
	int	i;

	i = 0;
	while (hold[i] != '\0')
	{
		if (hold[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*whole_line;
	static char	*hold;

	whole_line = malloc(sizeof(char) * 1);
	hold = malloc(sizeof(char) * BUFFER_SIZE);
	if (fd < 0 || hold == NULL || whole_line == NULL)
		return (NULL);
	whole_line = "\0";
	read(fd, hold, BUFFER_SIZE);
	hold[BUFFER_SIZE] = '\0';
	if (hold_check(hold) == 0)
	{
	}
	if (hold_check(hold) == 1)
	{
	}
	return (whole_line);
}

int	main(void)
{
	char	*ptr;
	int	fd;
	int	a;

	ptr = malloc(sizeof(char) * 15);
	if (ptr == NULL)
		return (-1);
	fd = open("test.txt", O_RDWR);
	ptr = get_next_line(fd);
	printf("%s\n", ptr);
	// ptr = get_next_line(fd);
	// printf("%s\n", ptr);
	close(fd);
	return (0);
}