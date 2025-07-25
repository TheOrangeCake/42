/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:32:44 by masase            #+#    #+#             */
/*   Updated: 2025/07/10 18:58:45 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	skip_space(char *line, int *i)
{
	if (!line)
		return ;
	while (ft_isspace(line[*i]) && line[*i])
		(*i)++;
}

void	skip_alpha(char *line, int *i)
{
	if (!line)
		return ;
	while (ft_isalpha(line[*i]) && line[*i])
		(*i)++;
}

bool	skip_sign_and_number(char *line, int *i)
{
	int	sign;

	sign = 0;
	if (!line)
		return (false);
	while (ft_isdigit_point(line[*i]) && line[*i])
	{
		if (line[*i] == '+' || line[*i] == '-')
			sign++;
		if (((ft_isdigit(line[*i]) && line[*i + 1] == '-')
				|| line[*i + 1] == '+'))
			return (ft_error("there is a sign in a wrong place"));
		if (sign > 1)
			return (ft_error("there is too much sign"));
		(*i)++;
	}
	return (true);
}
