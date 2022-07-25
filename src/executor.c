/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:27 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 14:36:52 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

void	cmd_pathfinder_utils(char **pcmd, char *env_path)
{
	int		i;
	char	*cmd;
	char	*cmd_path;
	char	**paths;

	paths = ft_split(env_path, ':');
	cmd = *pcmd;
	(*pcmd) = ft_strjoin("/", cmd);
	free(cmd);
	cmd = *pcmd;
	*pcmd = NULL;
	i = 0;
	while (paths && paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			*pcmd = cmd_path;
			break ;
		}
		free(cmd_path);
		i++;
	}
	free(cmd);
	ft_freetbl(paths, -1);
}

void	cmd_pathfinder(char **pcmd, char **env)
{
	char	*env_path;

	env_path = env_findkeyvalue("PATH", env);
	if (env_path == NULL)
	{
		free(*pcmd);
		*pcmd = NULL;
		return ;
	}
	if (*pcmd && env_path)
		cmd_pathfinder_utils(pcmd, env_path);
	free(env_path);
}

int	args_to_ac(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void	executor(t_cmd_line *cmdl, char ***penv)
{
	char	**env;

	env = *penv;
	if (ft_strncmp(cmdl->cmd, "echo", ft_strlen("echo") + 1) == 0)
		builtin_echo(args_to_ac(cmdl->args), cmdl->args, STDOUT_FILENO);
	else if (ft_strncmp(cmdl->cmd, "cd", ft_strlen("cd") + 1) == 0)
		builtin_cd(args_to_ac(cmdl->args), cmdl->args, penv);
	else if (ft_strncmp(cmdl->cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		builtin_pwd(args_to_ac(cmdl->args), STDOUT_FILENO);
	else if (ft_strncmp(cmdl->cmd, "export", ft_strlen("export") + 1) == 0)
		builtin_export(args_to_ac(cmdl->args), cmdl->args, penv, cmdl->fdout);
	else if (ft_strncmp(cmdl->cmd, "unset", ft_strlen("unset") + 1) == 0)
		builtin_unset(args_to_ac(cmdl->args), cmdl->args, penv);
	else if (ft_strncmp(cmdl->cmd, "env", ft_strlen("env") + 1) == 0)
		builtin_env(args_to_ac(cmdl->args), env, STDOUT_FILENO);
	else if (ft_strncmp(cmdl->cmd, "exit", ft_strlen("exit") + 1) == 0)
		builtin_exit(args_to_ac(cmdl->args), cmdl->args);
	else if (cmdl->cmd[0] == '\0')
		err_cmd_not_found(&g_sh, cmdl->cmd);
	else
		exec_bin(cmdl, env);
}
