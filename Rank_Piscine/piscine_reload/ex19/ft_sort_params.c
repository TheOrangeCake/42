/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:16:26 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/29 16:16:29 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcmp(char *dest, char *src)
{
	while (*dest == *src && *dest != '\0' && *src != '\0')
	{
		dest++;
		src++;
	}
	return (*dest - *src);
}

int	ft_swap(char **ptr0, char **ptr1)
{
	char	*temp_ptr;

	temp_ptr = *ptr0;
	*ptr0 = *ptr1;
	*ptr1 = temp_ptr;
	return (0);
}

char	*ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (str);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	j;

	j = 1;
	if (argc == 1)
		return (0);
	while (j == 1)
	{
		i = 1;
		while (i < argc - 1)
		{
			j = 0;
			if (ft_strcmp(argv[i], argv[i + 1]) > 0)
			{
				ft_swap(&argv[i], &(argv[i + 1]));
				j = 1;
			}
			i++;
		}
	}
	i = 1;
	while (i < argc)
		ft_putstr(argv[i++]);
}
