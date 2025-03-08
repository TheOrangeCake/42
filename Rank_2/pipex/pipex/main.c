/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/08 13:57:17 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_paths(char **envp)
{
	if (envp == NULL)
		return ("/");
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return ("/");
}

int	we_gonna_fork_this(t_pipex pipex, int ac, char **av, char **envp)
{
	(void)ac;
	pipex.i = 3;
	pipex.status = 0;
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		free_exit(pipex, 1);
	else if (pipex.pid1 == 0)
		process1(pipex, av, envp);
	pipex.pid3 = fork();
	if (pipex.pid3 < 0)
		free_exit(pipex, 1);
	else if (pipex.pid3 == 0)
		process3(pipex, pipex.i, av, envp);
	close_pipe1(pipex);
	waitpid(pipex.pid1, &pipex.status, 0);
	waitpid(pipex.pid3, &pipex.status, 0);
	pipex.code = WEXITSTATUS(pipex.status);
	if (pipex.code != 0 && pipex.code != 127 && pipex.code != 126)
		free_exit(pipex, 1);
	if (pipex.code == 127)
		return (free_split(pipex.paths), close_fd(pipex), 127);
	else if (pipex.code == 126)
		return (free_split(pipex.paths), close_fd(pipex), 126);
	return (free_split(pipex.paths), close_fd(pipex), 0);
}

int	run(t_pipex pipex, int ac, char **av, char **envp)
{
	pipex.fdo = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (pipex.fdo < 0)
		perror("Error");
	pipex.fdi = open(av[1], O_RDONLY);
	if (pipex.fdi < 0)
	{
		perror("Error");
		pipex.fdi = open("/dev/null", O_RDONLY);
	}
	if (pipe(pipex.pipe1) < 0)
		return (close_fd(pipex), 1);
	pipex.path_string = find_paths(envp);
	pipex.paths = ft_split(pipex.path_string, ':');
	if (pipex.paths == NULL)
		return (close_fd(pipex), close_pipe1(pipex), 1);
	pipex.code = we_gonna_fork_this(pipex, ac, av, envp);
	return (pipex.code);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	pipex.code = 0;
	if (ac == 5)
		pipex.code = run(pipex, ac, av, envp);
	else
		return (ft_printf("Input error\n"), 1);
	return (pipex.code);
}
