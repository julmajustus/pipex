/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:59:36 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/07 08:44:09 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_status(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		err("waitpid");
	if (WIFSIGNALED(status))
	{
		write(2, "Segmentation fault", 18);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
