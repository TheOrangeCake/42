/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:43 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/07 12:32:16 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
// #include "get_next_line.h"

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

char	*ft_strjoin(char const *s1, char const *s2)
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

int	buffer_check(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// char	*buffer_reset(char *buffer, char *whole_line)
// {
// 	if (buffer_check(buffer) == 1)
// 	{
// 		while (*buffer != '\n')
// 		{
// 			buffer++;
// 		}
// 		buffer++;
// 		whole_line = ft_strjoin(whole_line, buffer);
// 	}
// 	else
// 	{
// 		whole_line = ft_strjoin(whole_line, buffer);
// 		buffer = NULL;
// 	}
// 	return (whole_line);
// }

// char	*new_whole_line(int fd, char *buffer, size_t buffer_size, char *whole_line)
// {
// 	// int	i;

// 	// i = buffer_size
// 	while (buffer_check(buffer) == 0)
// 	{
// 		whole_line = ft_strjoin(whole_line, buffer);
// 		read(fd, buffer, buffer_size);
// 	}
// 		// if (i < buffer_size)
// 		// {
// 		// 	buffer[i + 1] = '\0';
// 		// 	whole_line = ft_strjoin(whole_line, buffer);
// 		// }
// 	return (whole_line);
// }

// char	*finish(char *buffer, char *whole_line)
// {
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	temp = malloc(sizeof(char) * ft_strlen(buffer) + 1);
// 	if (temp == NULL)
// 		return (NULL);
// 	while (buffer[i - 1] != '\n')
// 	{
// 		temp[i] = buffer[i];
// 		i++;
// 	}
// 	temp[i] = '\0';
// 	whole_line = ft_strjoin(whole_line, temp);
// 	free(temp);
// 	return (whole_line);
// }

// char	*get_next_line(int fd)
// {
// 	char		*whole_line;
// 	static char	*buffer;
// 	size_t		buffer_size;

// 	whole_line = malloc(sizeof(char) * 1);
// 	if (fd < 0 || whole_line == NULL)
// 		return (NULL);
// 	whole_line = "\0";
// 	buffer_size = BUFFER_SIZE;
// 	if (buffer != NULL)
// 		whole_line = buffer_reset(buffer, whole_line);
// 	else
// 	{
// 		buffer = malloc(sizeof(char) * buffer_size);
// 		if (buffer == NULL)
// 			return (NULL);
// 	}
// 	read(fd, buffer, buffer_size);
// 	if (buffer_check(buffer) == 0)
// 		whole_line = new_whole_line(fd, buffer, buffer_size, whole_line);
// 	if (buffer_check(buffer) == 1)
// 		whole_line = finish(buffer, whole_line);
// 	return (whole_line);
// }

char	*line_with_return(char *line, char *buffer)
{
	
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;
	size_t		buffer_size;
	
	line = malloc(sizeof(char) * 1);
	if (fd < 0 || whole_line == NULL)
		return (NULL);
	line = "\0";
	buffer_size = BUFFER_SIZE;
	if (buffer_check == 1)
	{
		line = line_with_return(line, buffer);
	}
	else
	{
		
	}
	return (line);
}

int	main(void)
{
	char	*ptr;
	int	fd;
	int	a;

	ptr = malloc(sizeof(char) * 100);
	if (ptr == NULL)
		return (-1);
	fd = open("test.txt", O_RDWR);
	ptr = get_next_line(fd);
	printf("%s", ptr);
	ptr = get_next_line(fd);
	printf("%s", ptr);
	close(fd);
	return (0);
}