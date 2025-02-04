/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 07:34:29 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/06 20:36:26 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	handle_nofds(int argc, char **argv)
{
	err_nofile(argv[1]);
	err_nofile(argv[argc -1]);
	exit (1);
}

static int	handle_no_infile(int argc, char **argv, char **envp)
{
	int	in_fd;
	int	i;

	err_nofile(argv[1]);
	in_fd = open("/dev/null", O_RDONLY);
	i = 3;
	while (i < argc - 2)
	{
		create_pipe_and_fork(&in_fd, argv[i], envp);
		i++;
	}
	last_p(in_fd, argv[argc - 3], argv[argc -1], envp);
	exit (0);
}

static int	handle_nofds_multiple_cmd(int argc, char **argv, char **envp)
{
	int	in_fd;
	int	i;

	err_nofile(argv[1]);
	err_nofile(argv[argc -1]);
	in_fd = open("/dev/null", O_RDONLY);
	i = 3;
	while (i < argc - 2)
	{
		create_pipe_and_fork(&in_fd, argv[i], envp);
		i++;
	}
	last_p(in_fd, argv[argc - 3], "/dev/null", envp);
	exit (1);
}

int	handle_pipex(int argc, char **argv, char **envp)
{
	int	in_fd;
	int	i;

	if (argc == 5 && argv[1][0] == '\0' && argv[argc - 1][0] == '\0')
		return (handle_nofds(argc, argv));
	else if (argc >= 5 && argv[1][0] == '\0' && argv[argc - 1][0] != '\0')
		return (handle_no_infile(argc, argv, envp));
	else if (argc > 5 && argv[1][0] == '\0' && argv[argc - 1][0] == '\0')
		return (handle_nofds_multiple_cmd(argc, argv, envp));
	else
	{
		open_infile(argv[1], &in_fd);
		i = 2;
		while (i < argc - 2)
		{
			create_pipe_and_fork(&in_fd, argv[i], envp);
			i++;
		}
		return (last_p(in_fd, argv[argc - 2], argv[argc - 1], envp));
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	retval;

	if (argc < 5)
	{
		ft_putstr_fd("Invalid number of arguments.\n", 2);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		retval = handle_heredoc(argc, argv, envp);
	else
		retval = handle_pipex(argc, argv, envp);
	while (wait(NULL) > 0)
		;
	return (retval);
}
