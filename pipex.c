/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 07:34:29 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/06 20:37:52 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_nofds(int argc, char **argv)
{
	err_nofile(argv[1]);
	err_nofile(argv[argc -1]);
	exit (1);
}

static int	handle_no_infile(int argc, char **argv, char **envp)
{
	int	in_fd;

	err_nofile(argv[1]);
	in_fd = open("/dev/null", O_RDONLY);
	if (in_fd == -1)
		err("open /dev/null");
	last_p(in_fd, argv[argc - 2], argv[argc - 1], envp);
	close(in_fd);
	exit (0);
}

int	handle_pipex(int argc, char **argv, char **envp)
{
	int	in_fd;
	int	i;

	if (argc >= 5 && argv[1][0] == '\0' && argv[argc - 1][0] == '\0')
		return (handle_nofds(argc, argv));
	else if (argc >= 5 && argv[1][0] == '\0' && argv[argc - 1][0] != '\0')
		return (handle_no_infile(argc, argv, envp));
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

	if (argc != 5)
	{
		ft_putstr_fd("Invalid number of arguments.\n", 2);
		return (1);
	}
	retval = handle_pipex(argc, argv, envp);
	while (wait(NULL) > 0)
		;
	return (retval);
}
