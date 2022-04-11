/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:57:15 by swillis           #+#    #+#             */
/*   Updated: 2022/04/11 23:31:51 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_fds(int file1, int file2)
{
	close(file1);
	close(file2);
	return (1);
}

char	*env_pathfinder(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (ft_substr(env[i], 5, (ft_strlen(env[i]) - 5)));
		i++;
	}
	return (NULL);
}

char	*cmd_pathfinder(char *cmd, char *env_path)
{
	char	**paths;
	char	*cmd_path;
	size_t	i;

	if (!cmd || !env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	i = 0;
	while (paths && paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		i++;
	}
	ft_freetbl(paths, -1);
	return (cmd_path);
}

char	*cmd_strfinder(char *str)
{
	char	**tbl;
	char	*cmd;
	char	*cmd_path;

	tbl = ft_split(str, ' ');
	cmd = ft_strdup(tbl[0]);
	ft_freetbl(tbl, -1);
	cmd_path = ft_strjoin("/", cmd);
	free(cmd);
	return (cmd_path);
}

char	**cmd_argstbl(char *str, char *path)
{
	char	**tbl;

	tbl = ft_split(str, ' ');
	free(tbl[0]);
	tbl[0] = ft_strdup(path);
	return (tbl);
}
