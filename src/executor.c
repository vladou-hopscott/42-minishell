/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:57:15 by swillis           #+#    #+#             */
/*   Updated: 2022/04/18 23:10:17 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		i++;
	}
	ft_freetbl(paths, -1);
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

char	*str_exportvalue(char **tbl)
{
	int		i;
	char	*value;

	if (tbl[1] == NULL)
		return (NULL);
	value = ft_strdup(tbl[1]);
	i = 2;
	while (tbl && tbl[i])
	{
		value = ft_strjoin(value, tbl[i]);
		i++;
	}
	return (value);
}

void	exec_export(t_token *token, char **env)
{
	int		i;
	char	**args;
	char	**tbl;
	char	*key;
	char	*value;

	args = ft_split(token->value, ' ');
	i = 1;
	while (args && args[i])
	{
		tbl = ft_split(args[i], '=');
		key = ft_strdup(tbl[0]);
		value = str_exportvalue(tbl);
		env = env_export(key, value, env);
		free(key);
		free(value);
		ft_freetbl(tbl, -1);
		i++;
	}
	ft_freetbl(args, -1);
}

char	**tbl_remove(char **tbl, char *key)
{
	int		i;
	int		pos;
	char	**new;

	pos = env_findkeypos(key, tbl);
	if (pos == -1)
		return (tbl);
	new = malloc(sizeof(char *) * (ft_tbllen(tbl)));
	if (!new)
		return (tbl);
	i = 0;
	while (tbl && tbl[i])
	{
		if (i != pos)
			new[i] = ft_strdup(tbl[i]);
		i++;
	}
	new[i] = NULL;
	ft_freetbl(tbl, -1);
	return (new);
}

void	exec_unset(t_token *token, char **env)
{
	int		i;
	char	**args;

	args = ft_split(token->value, ' ');
	i = 1;
	while (args && args[i])
	{
		env = tbl_remove(env, args[i]);
		i++;
	}
}

void	executor(t_token *token, char **env)
{
	char	*cmd;
	char	*path;
	char	**args;

	cmd = cmd_strfinder(token->value);
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		exec_export(token, env);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		exec_unset(token, env);
	path = env_findkeyvalue("PATH", env);
	cmd = cmd_pathfinder(cmd, path);
	if (!cmd)
		return ;
	args = cmd_argstbl(token->value, cmd);
	execve(cmd, args, env);
	free(cmd);
	free(path);
	ft_freetbl(args, -1);
}
