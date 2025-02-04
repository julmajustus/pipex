/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:33:04 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/06 20:34:06 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	last_p(int in_fd, char *cmd, char *outfile, char **envp)
{
	int		out_fd;
	pid_t	pid;

	if (outfile == NULL || outfile[0] == '\0')
	{
		err_nofile(outfile);
		close(in_fd);
		return (1);
	}
	open_outfile(outfile, &out_fd, 0);
	pid = fork();
	if (pid == -1)
		err("fork");
	if (pid == 0)
		child_p(in_fd, out_fd, cmd, envp);
	close(in_fd);
	close(out_fd);
	return (check_status(pid));
}
