/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:06:07 by hoannguy          #+#    #+#             */
/*   Updated: 2024/09/29 16:06:26 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*ptr;
	int	*table;

	if (min >= max)
		return (NULL);
	ptr = malloc(sizeof(int) * (max - min));
	if (ptr == NULL)
		return (NULL);
	table = ptr;
	while (min < max)
	{
		*ptr = min;
		ptr++;
		min++;
	}
	return (table);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	min;
// 	int	max;
// 	int	*result;
// 	int	i;

// 	min = -9;
// 	max = 9;
// 	result = ft_range(min, max);

// 	if (result == NULL)
// 	{
// 		printf("The result is NULL\n");
// 		return (0);
// 	}
// 	i = 0;
// 	while (i < (max - min))
// 	{
// 		printf("Result: %d\n", result[i]);
// 		i++;
// 	}
// 	return (0);
// }