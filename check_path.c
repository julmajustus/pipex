/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:40:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/06 19:18:03 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*check_path(char *cmd, char **env_path)
{
	int		i;
	char	*add_slash;
	char	*path;

	i = 0;
	while (env_path[i])
	{
		add_slash = ft_strjoin(env_path[i], "/");
		path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	**get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*get_path(char **cmd, char **envp)
{
	char	**env_path;
	char	*path;

	if (access(*cmd, F_OK | X_OK) == 0)
		return (ft_strdup(*cmd));
	env_path = get_env_path(envp);
	if (!env_path)
	{
		free_arr(env_path);
		exit_no_file(cmd);
		return (NULL);
	}
	path = check_path(*cmd, env_path);
	free_arr(env_path);
	if (!path)
	{
		if (*cmd[0] == '/')
			err_nofile(*cmd);
		else
			err_cmd_notfound(*cmd);
		free_arr(cmd);
		exit (127);
		return (NULL);
	}
	return (path);
}
