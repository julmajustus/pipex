/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:15:36 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/07 08:52:19 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_cmd(char *cmd)
{
	int	fd;

	if (ft_str_is_whitespace(cmd))
		return (1);
	fd = open(cmd, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (2);
	}
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
		return (3);
	return (0);
}

char	**cmd_validator(char **cmd)
{
	int		cmd_check;

	if (*cmd)
	{
		cmd_check = check_cmd(*cmd);
		if (cmd_check == 1)
			exit_cmd_notfound(cmd);
		else if (cmd_check == 2)
			exit_is_directory(cmd);
		else if (cmd_check == 3)
			exit_no_permission(cmd);
	}
	else
	{
		ft_putstr_fd(" : command not found\n", 2);
		free_arr(cmd);
		exit(127);
	}
	return (cmd);
}
