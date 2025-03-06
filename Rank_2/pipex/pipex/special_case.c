/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:31:51 by hoannguy          #+#    #+#             */
/*   Updated: 2025/03/06 06:22:28 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	stdin_read(t_pipex pipex)
{
	if (dup2(pipex.fdi, 1) < 0)
	{
		close(pipex.fdi);
		exit_unlink(".temp");
	}
	while (1)
	{
		pipex.line = get_next_line(0);
		if (pipex.line == NULL)
		{
			free(pipex.line);
			get_next_line(-100);
			break ;
		}
		ft_printf("%s", pipex.line);
		free(pipex.line);
	}
}

int	stdin_case(t_pipex pipex, int ac, char **av, char **envp)
{
	pipex.fdi = open(".temp", O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (pipex.fdi < 0)
		exit(1);
	stdin_read(pipex);
	pipex.fdo = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (pipex.fdo < 0)
		return (close(pipex.fdi), exit_unlink(".temp"), 1);
	if (pipe(pipex.pipe1) < 0)
		return (close(pipex.fdi), close(pipex.fdo),
			exit_unlink(".temp"), 1);
	pipex.path_string = find_paths(envp);
	pipex.paths = ft_split(pipex.path_string, ':');
	if (pipex.paths == NULL)
		return (close(pipex.fdi), close(pipex.fdo),
			close_pipe1(pipex), exit_unlink(".temp"), 1);
	close(pipex.fdi);
	pipex.fdi = open(".temp", O_RDONLY);
	pipex.exit_code = we_gonna_fork_this(pipex, ac, av, envp);
	if (unlink(".temp") < 0)
	{
		perror("Unlink eror");
		exit(1);
	}
	return (pipex.exit_code);
}

char	**awk_with_file(t_pipex pipex, int i, char *cmd)
{
	char	*temp;

	i = 0;
	while (!(cmd[i] == '\'' && cmd[i + 1] == ' '))
		i++;
	i++;
	temp = cmd + i + 1;
	cmd[i] = '\0';
	cmd = ft_strtrim(cmd, "'");
	if (cmd == NULL)
		return (NULL);
	pipex.cmd_list[1] = ft_strdup(cmd);
	if (pipex.cmd_list[1] == NULL)
		return (NULL);
	if (*temp == '"')
	{
		temp = ft_strtrim(temp, "\"");
		if (temp == NULL)
			return (NULL);
	}
	pipex.cmd_list[2] = ft_strdup(temp);
	if (pipex.cmd_list[2] == NULL)
		return (NULL);
	pipex.cmd_list[3] = NULL;
	return (pipex.cmd_list);
}

char	**awk_no_file(t_pipex pipex, char *cmd)
{
	char	*temp;

	temp = ft_strtrim(cmd, "'");
	if (temp == NULL)
		return (NULL);
	pipex.cmd_list[1] = ft_strdup(temp);
	if (pipex.cmd_list[1] == NULL)
		return (NULL);
	pipex.cmd_list[2] = NULL;
	return (pipex.cmd_list);
}

char	**awk_case(t_pipex pipex, char *cmd)
{
	int	i;

	i = 0;
	pipex.cmd_list = malloc(sizeof(char *) * 4);
	if (pipex.cmd_list == NULL)
		free_exit(pipex);
	pipex.cmd_list[0] = ft_strdup("awk");
	if (pipex.cmd_list[0] == NULL)
	{
		free(pipex.cmd_list);
		free_exit(pipex);
	}
	while (*cmd != '\'')
		cmd++;
	while (cmd[i + 1] != '\0')
		i++;
	if (cmd[i] == '\'')
		pipex.cmd_list = awk_no_file(pipex, cmd);
	else
		pipex.cmd_list = awk_with_file(pipex, i, cmd);
	if (pipex.cmd_list == NULL)
		return (free_split(pipex.cmd_list), NULL);
	return (pipex.cmd_list);
}
