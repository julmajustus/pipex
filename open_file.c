/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:15:38 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/06 12:04:41 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_outfile(char *outfile, int *out_fd, int append)
{
	if (append)
		*out_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out_fd == -1 && access(outfile, F_OK))
	{
		err_nofile(outfile);
		exit (1);
	}
	else if (*out_fd == -1 && !access(outfile, F_OK))
	{
		err_no_permission(outfile);
		exit (1);
	}
}

void	open_infile(char *infile, int *in_fd)
{
	*in_fd = open(infile, O_RDONLY);
	if (*in_fd == -1 && access(infile, F_OK))
	{
		err_nofile(infile);
	}
	else if (*in_fd == -1 && !access(infile, F_OK))
	{
		err_no_permission(infile);
	}
}
