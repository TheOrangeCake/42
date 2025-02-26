/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:33 by hoannguy          #+#    #+#             */
/*   Updated: 2025/02/26 20:10:49 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "stdio.h"

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		pipe[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*path_string;
	char	**paths;
} t_pipex;

#endif