/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/02/26 20:33:35 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_paths(char **envp)
{
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac >= 5)
	{
		// if (ft_strncmp(av[1], "here_doc", 7))
		// 	return (bonus(pipex, ac, av, envp), 0);
		pipex.fd_infile = open(av[1], O_RDONLY);
		if (pipex.fd_infile < 0)
			return (write(2, "fail to open infile\n", 20), 1);
		pipex.fd_outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (pipex.fd_outfile < 0)
			return (write(2, "fail to open outfile\n", 21), 1);
		if (pipe(pipex.pipe) < 0)
			return (write(2, "fail to create pipe\n", 20), 1);
		pipex.path_string = find_paths(envp);
		pipex.paths = ft_split(pipex.path_string, ':');
		we_gonna_fork_this(pipex, av, ac);
	}
	else
		write(2, "Not enough argument\n", 20);
	return (0);
}

// while (*pipex.paths != NULL)
// {
// 	ft_printf("%s\n", *pipex.paths);
// 	pipex.paths++;
// }