/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 11:44:47 by swillis          ###   ########.fr       */
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
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Please use a valid fd...\n", 2);
		exit(FAILURE);
	}
}

int	check_exec_bin(t_cmd_line *cmdl, char **env)
{
	char	*cpy;

	if (cmdl->cmd == NULL)
		return (FAILURE);
	cpy = ft_strdup(cmdl->cmd);
	if (cpy == NULL)
		return (FAILURE);
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

int	main(int argc, char **argv, char **env)
{
	check_program_args(argc);
	init_program_values(&g_sh, env);
	while (argv)
	{
		handle_signals(0);
		listen_prompt(&g_sh);
		lexer(&g_sh);
		parser(&g_sh);
		if (g_sh.error)
		{
			free_values(&g_sh, SUCCESS, 1);
			init_prompt_values(&g_sh);
			continue ;
		}
		execute_pipes(&g_sh);
		free_values(&g_sh, SUCCESS, 1);
		if (!g_sh.error)
			g_sh.exit_status = SUCCESS;
		init_prompt_values(&g_sh);
	}
	free_values(&g_sh, FAILURE, 1);
	if (g_sh.error == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
