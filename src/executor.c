/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:27 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 19:12:33 by vnafissi         ###   ########.fr       */
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
		builtin_env(args_to_ac(cmdl->args), (*penv), STDOUT_FILENO);
	else if (ft_strncmp(cmdl->cmd, "exit", ft_strlen("exit") + 1) == 0)
		builtin_exit(args_to_ac(cmdl->args), cmdl->args);
	else if (cmdl->cmd[0] == '\0')
	{
		if (!cmdl->cmd_is_empty_doll)
			err_cmd_not_found(&g_sh, cmdl->cmd);
		if (g_sh.has_pipe)
			ft_free_values_exit(&g_sh, SUCCESS, 1);
	}
	else
		exec_bin(cmdl, (*penv));
}
