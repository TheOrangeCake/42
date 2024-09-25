/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:48:12 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/22 17:54:50 by hoannguy         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*ptr;

	ptr = src;
	i = 0;
	ptr = malloc(ft_strlen(src) + 1);
	if (malloc(ft_strlen(src) + 1) == NULL)
		return (NULL);
	while (src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

#include <stdio.h>

int	main(void)
{
	char	test[40] = "hello, i am a cat";

	printf("result: %s\n", test);
	printf("result: %s\n", ft_strdup(test));
	return (0);
}