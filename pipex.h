/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 07:34:29 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/07 16:09:11 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>
# include <string.h>
# include <errno.h>

# define ARG_ARR_SIZE 8

typedef enum e_state
{
	OUTSIDE,
	INSIDE_SINGLE_QUOTE,
	INSIDE_DOUBLE_QUOTE,
	ESCAPE_SEQUENCE
}	t_state;

typedef struct s_parse_state
{
	char	**args;
	char	*arg;
	size_t	argc;
	size_t	arg_size;
	t_state	state;
}	t_parse_state;

void	err(const char *msg);
void	err_cmd_notfound(char *cmd);
void	err_nofile(char *file);
void	err_is_directory(char *cmd);
void	err_no_permission(char *cmd);
void	exit_cmd_notfound(char **cmd);
void	exit_is_directory(char **cmd);
void	exit_no_permission(char **cmd);
void	exit_no_file(char **cmd);
void	free_arr(char **arr);
int		exec_p(char *argv, char **envp);
char	**parse_arguments(char *cmd);
char	**add_arg(char **args, char *arg, size_t *argc, size_t *arg_size);
char	*append_char(char *str, char c);
char	*get_path(char **cmd, char **envp);
int		ft_str_is_whitespace(char *str);
char	**cmd_validator(char **cmd);
void	open_infile(char *infile, int *in_fd);
void	open_outfile(char *outfile, int *out_fd, int append);
int		check_status(pid_t pid);
void	create_pipe_and_fork(int *in_fd, char *cmd, char **envp);
int		child_p(int in_fd, int out_fd, char *cmd, char **envp);
int		check_status(pid_t pid);
int		last_p(int in_fd, char *cmd, char *outfile, char **envp);

#endif
