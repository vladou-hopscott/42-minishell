/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/18 11:54:14 by vladimir         ###   ########.fr       */
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
	char	*cpy;

	cpy = ft_strdup(cmdl->cmd);
	if (access(cpy, F_OK) != 0)
		cmd_pathfinder(&cpy, env);
	if (cpy == NULL)
	{
		free(cpy);
		return (FAILURE);
	}
	free(cpy);
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

// CANNOT USE THISE FUNCTION BEFORE EXECUTION.
// CHECK NEEDS TO BE DONE WITHIN EACH cmdl EXECUTION
// void	check_cmds(t_sh *sh)
// {
// 	t_cmd_line	*cmdl;
// 	char		**env;

// 	env = sh->env;
// 	cmdl = sh->cmd_line_lst;
// 	while (cmdl)
// 	{
// 		if (!cmdl->cmd)
// 		{
// 			sh->error = 1;
// 			sh->exit_status = SUCCESS;
// 			return ;
// 		}
// 		if (check_cmd(cmdl, env) == FAILURE)
// 		{
// 			err_cmd_not_found(&g_sh, cmdl->cmd);
// 			return ;
// 		}
// 		cmdl = cmdl->next;
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	check_program_args(argc);
	init_program_values(&g_sh, env);
	while (argv)
	{
		handle_signals();
		listen_prompt(&g_sh);
		lexer(&g_sh);
		parser(&g_sh);
		if (g_sh.error)
		{
			free_values(&g_sh, SUCCESS);
			init_prompt_values(&g_sh);
			continue ;
		}
		execute_pipes(&g_sh);
		free_values(&g_sh, SUCCESS);
		if (!g_sh.error)
			g_sh.exit_status = SUCCESS;
		init_prompt_values(&g_sh);
	}
	free_values(&g_sh, FAILURE);
	if (g_sh.error == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
