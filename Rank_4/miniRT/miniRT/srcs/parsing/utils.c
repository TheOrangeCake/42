/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:11:43 by maw               #+#    #+#             */
/*   Updated: 2025/07/10 19:02:18 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ft_isdigit_point(int c)
{
	if ((((c >= '0' && c <= '9') || c == '.') || c == '+') || c == '-')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

float	ft_atof(const char *str)
{
	int		i;
	int		signe;
	float	resultat;

	resultat = 0.0f;
	signe = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = resultat * 10 + (str[i] - '0');
		i++;
	}
	decimal_atof(i, str, &resultat);
	return (resultat * signe);
}

void	decimal_atof(int i, const char *str, float *resultat)
{
	float	fraction;

	fraction = 0.1;
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			*resultat += (str[i] - '0') * fraction;
			fraction *= 0.1;
			i++;
		}
	}
}
