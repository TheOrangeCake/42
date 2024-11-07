/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:43 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/07 19:32:35 by hoannguy         ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
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

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
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

char	*line_with_return(char *line, char **buffer)
{
	int		i;
	char	*temp;
	char	*temp1;
	
	i = 0;
	temp = malloc(sizeof(char) * ft_strlen(*buffer) + 1);
	if (temp == NULL)
		return (NULL);
	while ((*buffer)[i] != '\n')
	{
		temp[i] = (*buffer)[i];
		i++;
	}
	temp[i] = (*buffer)[i];
	i++;
	temp[i] = '\0';
	temp1 = ft_strjoin(line, temp);
	*buffer = *buffer + i;
	free(temp);
	free(line);
	return (temp1);
}

char	*line_without_return(int fd, char *line, char **buffer, size_t buffer_size)
{
	int		i;
	char	*temp;
	
	line = ft_strjoin(line, *buffer);
	*buffer = ft_memset(*buffer, '\0', buffer_size);
	i = read(fd, *buffer, buffer_size);
	if (i < 0)
		return (NULL);
	// (*buffer)[buffer_size] = '\0';
	if (buffer_check(*buffer) == 1)
	{
		line = line_with_return(line, buffer);
		return (line);
	}
	else
	{
		if (i < buffer_size)
		{
			(*buffer)[i] ='\0';
			line = ft_strjoin(line, *buffer);
			return (line);
		}
		return( line_without_return(fd, line, buffer, buffer_size));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;
	size_t		buffer_size;

	if (fd < 0)
		return (NULL);
	line = "\0";
	buffer_size = BUFFER_SIZE;
	if (buffer == NULL)
	{
		buffer = malloc(sizeof(char) * buffer_size);
		if (buffer == NULL)
			return (NULL);
	}
	if (buffer_check(buffer) == 1)
		line = line_with_return(line, &buffer);
	else
		line = line_without_return(fd, line, &buffer, buffer_size);
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
	printf("line1: %s", ptr);

	ptr = get_next_line(fd);
	printf("line2: %s", ptr);
	
	ptr = get_next_line(fd);
	printf("line3: %s", ptr);
	close(fd);
	return (0);
}