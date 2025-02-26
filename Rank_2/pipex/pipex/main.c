/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/02/27 00:07:29 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **list)
{
	int	i;

	i = 0;
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
}

char	*find_paths(char **envp)
{
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

void	we_gonna_fork_this(t_pipex pipex, char **av, char **envp)
{
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		process1(pipex, av, envp);
	// waitpid(pipex.pid1, NULL, 0);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		process2(pipex, av, envp);
	// waitpid(pipex.pid2, NULL, 0);
	free_split(pipex.paths);
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
		we_gonna_fork_this(pipex, av, envp);
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