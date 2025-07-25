/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:15:58 by maw               #+#    #+#             */
/*   Updated: 2024/08/23 17:24:10 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	int		i;
	int		len;
	char	*dup;

	len = ft_strlen(source);
	i = 0;
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (dup);
	while (source[i])
	{
		dup[i] = source[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
