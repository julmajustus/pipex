/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:37:46 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/06 20:36:35 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_p(int in_fd, int out_fd, char *cmd, char **envp)
{
	if (dup2(in_fd, 0) == -1)
		exit (1);
	if (dup2(out_fd, 1) == -1)
		return (1);
	close(in_fd);
	close(out_fd);
	return (exec_p(cmd, envp));
}

void	create_pipe_and_fork(int *in_fd, char *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		err("pipe");
	pid = fork();
	if (pid == -1)
		err("fork");
	if (pid == 0)
	{
		close(fd[0]);
		child_p(*in_fd, fd[1], cmd, envp);
		exit (1);
	}
	close(fd[1]);
	close(*in_fd);
	*in_fd = fd[0];
	if (*in_fd == -1)
	{
		close(fd[0]);
		err("pipe");
	}
}

int	exec_p(char *argv, char **envp)
{
	int		retval;
	char	*path;
	char	**cmd;

	cmd = parse_arguments(argv);
	cmd = cmd_validator(cmd);
	path = get_path(cmd, envp);
	retval = execve(path, cmd, envp);
	free_arr(cmd);
	free(path);
	if (retval == -1)
		exit (1);
	return (retval);
}
