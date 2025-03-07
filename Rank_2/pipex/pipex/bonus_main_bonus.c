/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:56:11 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/07 23:29:23 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	we_gonna_fork_this(t_pipex pipex, int ac, char **av, char **envp)
{
	pipex.i = 3;
	pipex.status = 0;
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		free_exit(pipex);
	else if (pipex.pid1 == 0)
		process1(pipex, av, envp);
	if (ac > 5)
		loop2(&pipex, ac, av, envp);
	pipex.pid3 = fork();
	if (pipex.pid3 < 0)
		free_exit(pipex);
	else if (pipex.pid3 == 0)
		process3(pipex, pipex.i, av, envp);
	close_pipe1(pipex);
	wait_all(pipex, &pipex.status, ac);
	pipex.code = WEXITSTATUS(pipex.status);
	if (pipex.code != 0 && pipex.code != 127 && pipex.code != 126)
		free_exit(pipex);
	if (pipex.code == 127)
		return (free_split(pipex.paths), close_fd(pipex), 127);
	else if (pipex.code == 126)
		return (free_split(pipex.paths), close_fd(pipex), 126);
	return (free_split(pipex.paths), close_fd(pipex), 0);
}

void	bonus_read(t_pipex pipex, char *LIMITER)
{
	if (dup2(pipex.fdi, 1) < 0)
		exit_unlink(".temp");
	while (1)
	{
		pipex.line = get_next_line(0);
		if (pipex.line == NULL
			|| !ft_strncmp(pipex.line, LIMITER, ft_strlen(LIMITER)))
		{
			free(pipex.line);
			get_next_line(-100);
			break ;
		}
		ft_printf("%s", pipex.line);
		free(pipex.line);
	}
}

int	bonus(t_pipex pipex, int ac, char **av, char **envp)
{
	pipex.fdi = open(".temp", O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (pipex.fdi < 0)
		return (1);
	bonus_read(pipex, av[2]);
	pipex.fdo = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0000644);
	if (pipex.fdo < 0)
		perror("Error");
	if (pipe(pipex.pipe1) < 0)
		exit_unlink(".temp");
	pipex.path_string = find_paths(envp);
	pipex.paths = ft_split(pipex.path_string, ':');
	if (pipex.paths == NULL)
		exit_unlink(".temp");
	av++;
	ac--;
	close(pipex.fdi);
	pipex.fdi = open(".temp", O_RDONLY);
	pipex.code = we_gonna_fork_this(pipex, ac, av, envp);
	if (unlink(".temp") < 0)
	{
		perror("Unlink eror");
		exit(1);
	}
	return (pipex.code);
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
	if (pipex.path_string != NULL)
	{
		pipex.paths = ft_split(pipex.path_string, ':');
		if (pipex.paths == NULL)
			return (close_fd(pipex), close_pipe1(pipex), 1);
	}
	pipex.code = we_gonna_fork_this(pipex, ac, av, envp);
	return (pipex.code);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	pipex.code = 0;
	if (ac >= 5)
	{
		if (!ft_strncmp(av[1], "here_doc", 8) && ac >= 6)
			pipex.code = bonus(pipex, ac, av, envp);
		else
			pipex.code = run(pipex, ac, av, envp);
	}
	else
		return (ft_printf("Input error\n"), 1);
	return (pipex.code);
}
