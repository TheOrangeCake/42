/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:21:32 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/13 20:50:22 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_line(const char *s, int *signal)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			i++;
			*signal = 1;
			return (i);
		}
		i++;
	}
	return (i);
}

char	*ft_strjoin_line(char **s1, char *s2, int *signal, size_t *buffer_mover)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	ptr = malloc(ft_strlen_line(*s1, signal) + ft_strlen_line(s2, signal) + 1);
	if (ptr == NULL)
		return (safe_free(s1));
	i = 0;
	j = 0;
	while ((*s1)[i])
	{
		ptr[i] = (*s1)[i];
		i++;
	}
	while (s2[j] && s2[j] != '\n')
	{
		ptr[i++] = s2[j++];
	}
	if (s2[j] == '\n')
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	*buffer_mover = j;
	safe_free(s1);
	return (ptr);
}

char	*start(char **line, int fd, char **buffer, size_t buffer_size)
{
	size_t	i;
	int		signal;
	size_t	buffer_mover;

	signal = 0;
	buffer_mover = 0;
	i = read(fd, *buffer, buffer_size);
	if ((*buffer)[0] == '\0' && (*line)[0] == '\0' && i == 0)
	{
		safe_free(buffer);
		return (safe_free(line));
	}
	(*buffer)[i] = '\0';
	*line = ft_strjoin_line(line, *buffer, &signal, &buffer_mover);
	if (*line == NULL)
		return (safe_free(buffer));
	if (signal == 1 || i < buffer_size)
	{
		i = 0;
		while ((*buffer)[buffer_mover])
			(*buffer)[i++] = (*buffer)[buffer_mover++];
		(*buffer)[i] = '\0';
		return (*line);
	}
	return (start(line, fd, buffer, buffer_size));
}

char	*end(char **line, int fd, char **buffer, size_t buffer_size)
{
	int		signal;
	size_t	buffer_mover;
	int		i;

	signal = 0;
	buffer_mover = 0;
	*line = ft_strjoin_line(line, *buffer, &signal, &buffer_mover);
	if (*line == NULL)
		return (safe_free(buffer));
	if (signal == 1)
	{
		i = 0;
		while ((*buffer)[buffer_mover])
			(*buffer)[i++] = (*buffer)[buffer_mover++];
		(*buffer)[i] = '\0';
		return (*line);
	}
	else
	{
		(*buffer)[0] = '\0';
		*line = start(line, fd, buffer, buffer_size);
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1024];

	line = malloc(sizeof(char) * 1);
	if (line == NULL || read(fd, 0, 0) < 0 || BUFFER_SIZE < 0)
	{
		safe_free(&line);
		return (safe_free(&(buffer[fd])));
	}
	line[0] = '\0';
	if (buffer[fd] == NULL)
	{
		buffer[fd] = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (buffer[fd] == NULL)
			return (safe_free(&line));
		buffer[fd][0] = '\0';
		line = start(&line, fd, &(buffer[fd]), BUFFER_SIZE);
	}
	else
		line = end(&line, fd, &(buffer[fd]), BUFFER_SIZE);
	return (line);
}

// int	main(void)
// {
// 	char	*ptr;
// 	int	fd;

// 	fd = open("test.txt", O_RDWR);
// 	ptr = get_next_line(fd);
// 	printf("line1: %s", ptr);
// 	free(ptr);
// 	ptr = get_next_line(fd);
// 	printf("line2: %s", ptr);
// 	free(ptr);
// 	ptr = get_next_line(fd);
// 	printf("line3: %s", ptr);
// 	free(ptr);
// 	close(fd);
// 	return (0);
// }

		// i = 0;
		// while (buffer[buffer_mover])
		// 	buffer[i++] = buffer[buffer_mover++];
		// buffer[i] = '\0';
