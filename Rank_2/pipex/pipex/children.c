/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:52:43 by hoannguy          #+#    #+#             */
/*   Updated: 2025/02/26 23:08:47 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process1(t_pipex pipex, char **av, char **envp)
{
	ft_printf("child_1\n");
}

void	process2(t_pipex pipex, char **av, char **envp)
{
	ft_printf("child_2\n");
}
