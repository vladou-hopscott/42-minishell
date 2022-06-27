/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/27 22:49:51 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
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

void	execute_cmds(t_sh *sh)
{
	t_cmd_line	*cmdl;

	cmdl = sh->cmd_line_lst;
	while (cmdl)
	{
		executor(cmdl, &sh->env);
		cmdl = cmdl->next;
	}
}

// ============= MULTIPIPE ==========================================

int	spawn_process(int fdin, int fdout, t_cmd_line *cmdl, t_sh *sh)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (fdin != STDIN_FILENO)
		{
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		if (fdout != STDOUT_FILENO)
		{
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
		executor(cmdl, &sh->env);
		return (0);
	}
	return (pid);
}

int	execute_pipes(t_sh *sh)
{
	int 		i;
	int 		fdin;
	int 		fdout;
	int 		n;
	int			fd[2];
	t_cmd_line	*cmdl;
	char		**env;

	env = sh->env;
	cmdl = sh->cmd_line_lst;;
	cmdl = cmdl->next;
	n = 0;
	while (cmdl)
	{
		n++;
		fdout = cmdl->fdout;
		cmdl = cmdl->next;
	}
	cmdl = sh->cmd_line_lst;
	fdin = cmdl->fdin;
	i = 0;
	while (i < n)
	{
		pipe(fd);
		spawn_process(fdin, fd[1], cmdl, sh);
		close(fd[1]);
		fdin = fd[0];
		cmdl = cmdl->next;
		i++;
	}
	spawn_process(fdin, fdout, cmdl, sh);
	return (0);
}

// ======================================

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
