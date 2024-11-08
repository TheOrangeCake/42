/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:43 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/08 21:52:07 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*ptr;

// 	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i])
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		ptr[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	ptr[i] = '\0';
// 	free(s1);
// 	return (ptr);
// }

// int	buffer_check(char *buffer)
// {
// 	int	i;

// 	i = 0;
// 	while (buffer[i] != '\0')
// 	{
// 		if (buffer[i] == '\n')
// 		{
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// char	*line_with_return(char *line, char *buffer)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;

// 	i = 0;
// 	temp = malloc(sizeof(char) * ft_strlen(buffer) + 1);
// 	if (temp == NULL)
// 		return (NULL);
// 	while (buffer[i] != '\n')
// 	{
// 		temp[i] = buffer[i];
// 		i++;
// 	}
// 	temp[i] = buffer[i];
// 	i++;
// 	temp[i] = '\0';
// 	line = ft_strjoin(line, temp);
// 	j = 0;
// 	while (buffer[i] != '\0')
// 		buffer[j++] = buffer[i++];
// 	buffer[j] = '\0';
// 	free(temp);
// 	return (line);
// }

// char	*line_no_return(int fd, char *line, char *buffer, size_t buffer_size)
// {
// 	size_t		i;

// 	line = ft_strjoin(line, buffer);
// 	buffer[0] = '\0';
// 	i = read(fd, buffer, buffer_size);
// 	buffer[i] = '\0';
// 	if (buffer_check(buffer) == 1)
// 	{
// 		line = line_with_return(line, buffer);
// 	}
// 	else
// 	{
// 		if (i < buffer_size)
// 		{
// 			line = ft_strjoin(line, buffer);
// 			if (line[0] == '\0')
// 				return (NULL);
// 			return (line);
// 		}
// 		return (line_no_return(fd, line, buffer, buffer_size));
// 	}
// 	return (line);
// }

// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	static char	*buffer;
// 	size_t		buffer_size;

// 	line = malloc(sizeof(char) * 1);
// 	if (line == NULL || read(fd, 0, 0) < 0)
// 		return (NULL);
// 	line[0] = '\0';
// 	buffer_size = BUFFER_SIZE;
// 	if (buffer == NULL)
// 	{
// 		buffer = malloc(sizeof(char) * buffer_size);
// 		if (buffer == NULL)
// 			return (NULL);
// 	}
// 	if (buffer_check(buffer) == 1)
// 		line = line_with_return(line, buffer);
// 	else
// 		line = line_no_return(fd, line, buffer, buffer_size);
// 	return (line);
// }

// ---------------------------------------------------------------------

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

char	*ft_strjoin_line(char *s1, char *s2, int *signal, size_t *buffer_mover)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	ptr = malloc(ft_strlen_line(s1, signal) + ft_strlen_line(s2, signal) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
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
	free(s1);
	return (ptr);
}

char	*start(char *line, int fd, char *buffer, size_t buffer_size)
{
	size_t	i;
	int		signal;
	size_t	buffer_mover;

	signal = 0;
	buffer_mover = 0;
	i = read(fd, buffer, buffer_size);
	if (buffer[0] == '\0' && line[0] == '\0')
		return (NULL);
	buffer[i] = '\0';
	line = ft_strjoin_line(line, buffer, &signal, &buffer_mover);
	if (signal == 1 || i < buffer_size)
	{
		i = 0;
		while (buffer[buffer_mover])
			buffer[i++] = buffer[buffer_mover++];
		buffer[i] = '\0';
		return (line);
	}
	return (start(line, fd, buffer, buffer_size));
}

char	*end(char *line, int fd, char *buffer, size_t buffer_size)
{
	int		signal;
	size_t	buffer_mover;
	int		i;
	
	signal = 0;
	buffer_mover = 0;
	line = ft_strjoin_line(line, buffer, &signal, &buffer_mover);
	if (signal == 1)
	{
		i = 0;
		while (buffer[buffer_mover])
			buffer[i++] = buffer[(buffer_mover)++];
		buffer[i] = '\0';
		return (line);
	}
	else
	{
		buffer[0] = '\0';
		line = start(line, fd, buffer, buffer_size);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;
	size_t		buffer_size;

	line = malloc(sizeof(char) * 1);
	if (line == NULL || read(fd, 0, 0) < 0)
	{
		free(line);
		return (NULL);
	}
	line[0] = '\0';
	buffer_size = BUFFER_SIZE;
	if (buffer == NULL)
	{
		buffer = malloc(sizeof(char) * buffer_size + 1);
		if (buffer == NULL)
			return (NULL);
		line = start(line, fd, buffer, buffer_size);
	}
	else
		line = end(line, fd, buffer, buffer_size);
	return (line);
}

// int	main(void)
// {
// 	char	*ptr;
// 	int	fd;

// 	ptr = malloc(sizeof(char) * 100);
// 	if (ptr == NULL)
// 		return (-1);
// 	fd = open("test.txt", O_RDWR);
// 	ptr = get_next_line(fd);
// 	printf("line1: %s", ptr);
// 	ptr = get_next_line(fd);
// 	printf("line2: %s", ptr);
// 	// ptr = get_next_line(fd);
// 	// printf("line3: %s", ptr);
// 	// ptr = get_next_line(fd);
// 	// printf("line4: %s", ptr);
// 	// ptr = get_next_line(fd);
// 	// printf("line5: %s", ptr);
// 	// ptr = get_next_line(fd);
// 	// printf("line6: %s", ptr);
// 	// ptr = get_next_line(fd);
// 	// printf("line7: %s", ptr);
// 	// free(ptr);
// 	close(fd);
// 	return (0);
// }
