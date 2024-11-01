/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:13:43 by hoannguy          #+#    #+#             */
/*   Updated: 2024/11/01 16:18:13 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// char	*get_next_line(int fd)
// {

// }

int	main(void)
{
	char	*ptr;
	int	fd;
	int	a;

	ptr = malloc(sizeof(char) * 15);
	if (ptr == NULL)
		return (-1);
	fd = open("test.txt", O_RDWR);
	a = read(fd, ptr, 3);
	printf("%s\n", ptr);
	return (0);
}