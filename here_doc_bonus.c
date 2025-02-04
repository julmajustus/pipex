/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:49:04 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/06 22:58:17 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	heredoc_p(int in_fd, char *cmd, char *outfile, char **envp)
{
	int		out_fd;
	pid_t	pid;

	if (outfile == NULL || outfile[0] == '\0')
	{
		err_nofile(outfile);
		close(in_fd);
		return (1);
	}
	open_outfile(outfile, &out_fd, 1);
	pid = fork();
	if (pid == -1)
		err("fork");
	if (pid == 0)
		child_p(in_fd, out_fd, cmd, envp);
	close(in_fd);
	close(out_fd);
	return (check_status(pid));
}

static void	here_doc(char *limiter, int *fd)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		err("pipe");
	ft_putstr_fd("here_doc > ", 1);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd("here_doc > ", 1);
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(pipe_fd[1]);
	*fd = pipe_fd[0];
}

int	handle_heredoc(int argc, char **argv, char **envp)
{
	int	in_fd;
	int	i;

	if (argc < 6)
	{
		ft_putstr_fd("Invalid number of arguments.\n", 2);
		return (1);
	}
	here_doc(argv[2], &in_fd);
	i = 3;
	while (i < argc - 1)
	{
		create_pipe_and_fork(&in_fd, argv[i], envp);
		i++;
	}
	return (heredoc_p(in_fd, argv[argc - 2], argv[argc - 1], envp));
}
