/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/28 12:12:09 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	g_sh;

void	check_program_args(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		exit(FAILURE);
	}
}

int	check_exec_bin(t_cmd_line *cmdl, char **env)
{
	char	*cmd;

	cmd = ft_strdup(cmdl->cmd);
	if (access(cmd, F_OK) != 0)
		cmd_pathfinder(&cmd, env);
	if (cmd == NULL)
	{
		free(cmd);
		return (FAILURE);
	}
	free(cmd);
	return (SUCCESS);
}

int	check_cmd(t_cmd_line *cmdl, char **env)
{
	if (ft_strncmp(cmdl->cmd, "echo", ft_strlen("echo") + 1) == 0)
		return (SUCCESS);
	else if (ft_strncmp(cmdl->cmd, "cd", ft_strlen("cd") + 1) == 0)
		return (SUCCESS);
	else if (ft_strncmp(cmdl->cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		return (SUCCESS);
	else if (ft_strncmp(cmdl->cmd, "export", ft_strlen("export") + 1) == 0)
		return (SUCCESS);
	else if (ft_strncmp(cmdl->cmd, "unset", ft_strlen("unset") + 1) == 0)
		return (SUCCESS);
	else if (ft_strncmp(cmdl->cmd, "env", ft_strlen("env") + 1) == 0)
		return (SUCCESS);
	else if (ft_strncmp(cmdl->cmd, "exit", ft_strlen("exit") + 1) == 0)
		return (SUCCESS);
	else
		return (check_exec_bin(cmdl, env));
	return (FAILURE);
}

void	check_cmds(t_sh *sh)
{
	t_cmd_line	*cmdl;
	char		**env;

	env = sh->env;
	cmdl = sh->cmd_line_lst;;
	while (cmdl)
	{
		if (check_cmd(cmdl, env) == FAILURE)
		{
			err_cmd_not_found(&g_sh, cmdl->cmd);
			return ;
		}
		cmdl = cmdl->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	check_program_args(argc);
	handle_signals();
	init_program_values(&g_sh, env);
	while (1)
	{
		listen_prompt(&g_sh);
		lexer(&g_sh);
		parser(&g_sh);
		check_cmds(&g_sh);
		if (g_sh.error)
		{
			free_values(&g_sh, 0);
			init_prompt_values(&g_sh);
			continue ;
		}
		execute_pipes(&g_sh);
		free_values(&g_sh, 0);
		if (!g_sh.error)
			g_sh.exit_status = SUCCESS;
		init_prompt_values(&g_sh);
	}
	free_values(&g_sh, 1);
	if (g_sh.error == 1)
		return (1);
	return (0);
}
