/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:42:53 by maw               #+#    #+#             */
/*   Updated: 2025/06/14 19:06:35 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freestash(char *stash)
{
	free(stash);
	stash = NULL;
	return (stash);
}

char	*feedline(char *s)
{
	size_t	i;
	char	*feed;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
	{
		i++;
	}
	feed = ft_substr(s, 0, i + 1);
	if (!feed)
		return (NULL);
	return (feed);
}

static	char	*reading(int fd, char *stash, char *temp, char *buffer)
{
	int	readcount;

	readcount = 1;
	while (readcount > 0)
	{
		readcount = read(fd, buffer, BUFFER_SIZE);
		buffer[readcount] = '\0';
		if (stash == NULL)
		{
			stash = ft_strdup(buffer);
		}
		else
		{
			temp = ft_strjoin(stash, buffer);
			free(stash);
			stash = temp;
		}
		if (!stash || ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

static	char	*setupstash(char *stash, char *temp)
{
	if (ft_strchr(stash, '\n') != NULL)
	{
		temp = ft_strdup(ft_strchr(stash, '\n') + 1);
		if (!temp)
		{
			free(stash);
			return (NULL);
		}
		free(stash);
		stash = temp;
	}
	else
		stash = freestash(stash);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;
	char		*line;
	char		*temp;

	line = NULL;
	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		stash = freestash(stash);
		return (NULL);
	}
	stash = reading(fd, stash, temp, buffer);
	if (stash)
	{
		line = feedline(stash);
		stash = setupstash(stash, temp);
		if (!line || line[0] == '\0')
		{
			free(line);
			stash = freestash(stash);
			return (NULL);
		}
	}
	return (line);
}

// int main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 		{
// 			break ;
// 		}
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

// // objectif creer un buffer que je vais print
// puis ensuite freee ainsi de suite jusqua la fin
// de la laligne en gros

// Il faut que je soit capable de mofdifier la taiile
// de mon buffer en fonction de la tailler du buffersize donneer