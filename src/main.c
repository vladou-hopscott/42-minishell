/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/26 23:45:58 by swillis          ###   ########.fr       */
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

// ============= V1 ==================

// int	execute_pipes(t_sh *sh)
// {
// 	int 		i;
// 	int 		n;
// 	int 		npipe;
// 	int 		pid;
// 	int 		**fd;
// 	t_cmd_line	*cmdl;

// 	// count pipes
// 	npipe = 0;
// 	cmdl = sh->cmd_line_lst;
// 	cmdl = cmdl->next;
// 	while (cmdl)
// 	{
// 		npipe++;
// 		cmdl = cmdl->next;
// 	}

// 	// malloc tbl
// 	fd = malloc(sizeof(int *) * npipe);
// 	if (!fd)
// 		return (-1);
// 	i = 0;
// 	while (i < npipe)
// 	{
// 		fd[i] = malloc(sizeof(int) * 2);
// 		if (!fd[i])
// 			return (-1);
// 		i++;
// 	}

// 	// instantiate pipes in tbl
// 	i = 0;
// 	while (i < npipe)
// 		if (pipe(fd[i++]) == -1)
// 			return (-1);
    
// 	// loop over commands
// 	i = -1;
// 	cmdl = sh->cmd_line_lst;
// 	while (cmdl)
// 	{
// 		// fork process
// 		pid = fork();
// 		if (pid < 0)
// 			return (-1);
// 		if (pid == 0) {
// 			// close all other pipes
// 			n = 0;
// 			while (n < npipe)
// 			{
// 				if (n != i)
// 				{
// 					close(fd[n][0]);
// 					close(fd[n][1]);
// 				}
// 				n++;
// 			}
// 			if (i >= 0)
// 			{
// 				dup2(fd[i][0], STDIN_FILENO);
// 				// if not last cmd
// 				if (i < npipe - 1)
// 					dup2(fd[i][1], STDOUT_FILENO);
// 				// close pipe ends and exec
// 				close(fd[i][0]);
// 				close(fd[i][1]);
// 			}
// 			executor(cmdl, &sh->env);
// 		}
// 		cmdl = cmdl->next;
// 		i++;
// 	}
	
// 	// close all process in parallel
// 	while (wait(NULL) != -1)
// 		;
    
// 	// free tbl
// 	i = 0;
// 	while (i < npipe)
// 		free(fd[i++]);
// 	free(fd);
	
//     return (0);
// }

// ======================================

// ============= V2 ==================

// int	execute_pipes(t_sh *sh)
// {
// 	t_cmd_line	*cmdl;
// 	int 		fd[2];
// 	int			fdin;
// 	pid_t 		pid;

// 	fdin = STDIN_FILENO;
// 	cmdl = sh->cmd_line_lst;
// 	while (cmdl) 
// 	{
// 		fdin = fd[0];
// 		if (pipe(fd) == -1)
// 			return (-1);
// 		pid = fork();
// 		if (pid < 0)
// 			return (-1);
// 		else if (pid == 0) 
// 		{
// 			dup2(fdin, 0);
// 			if (cmdl->next != NULL)
// 				dup2(fd[1], STDOUT_FILENO);
// 			close(fd[0]);
// 			executor(cmdl, &sh->env);
// 		}
// 		wait(NULL);
// 		close(fd[0]);
// 		close(fd[1]);
// 		cmdl = cmdl->next;
// 	}
//     return (0);
// }

// // ============= V3 ==================

// int	execute_pipes(t_sh *sh)
// {
// 	int 		i;
// 	int 		n;
// 	int 		npipe;
// 	int 		pid;
// 	int 		*pids;
// 	int 		**fd;
// 	t_cmd_line	*cmdl;

// 	// count pipes
// 	npipe = 0;
// 	cmdl = sh->cmd_line_lst;
// 	cmdl = cmdl->next;
// 	while (cmdl)
// 	{
// 		npipe++;
// 		cmdl = cmdl->next;
// 	}

// 	if (npipe == 0)
// 	{
// 		executor(cmdl, &sh->env);
// 		return (0);
// 	}

// 	// malloc tbls
// 	pids = malloc(sizeof(int) * (npipe + 1));
// 	if (!pids)
// 		return (-1);
// 	fd = malloc(sizeof(int *) * npipe);
// 	if (!fd)
// 		return (-1);
// 	i = 0;
// 	while (i < npipe)
// 	{
// 		fd[i] = malloc(sizeof(int) * 2);
// 		if (!fd[i])
// 			return (-1);
// 		i++;
// 	}

// 	// instantiate pipes in tbl
// 	i = 0;
// 	while (i < npipe)
// 		if (pipe(fd[i++]) == -1)
// 			return (-1);

// 	// loop over commands
// 	i = 0;
// 	cmdl = sh->cmd_line_lst;
// 	while (cmdl)
// 	{
// 		printf("Running cmd[%d]: %s\n", i, cmdl->cmd);
// 		pid = fork();
// 		if (pid < 0)
// 			return (-1);
// 		// child process
// 		if (pid == 0) 
// 		{
// 			// dup2
// 			if (i > 0)
// 				dup2(fd[i - 1][0], STDIN_FILENO);
// 			if (i < npipe - 1)
// 				dup2(fd[i][1], STDOUT_FILENO);

// 			// exec
// 			executor(cmdl, &sh->env);
// 		}
// 		// parent process
// 		// close all pipes
// 		n = 0;
// 		while (n < npipe)
// 		{
// 			close(fd[n][0]);
// 			close(fd[n][1]);
// 			n++;
// 		}
// 		pids[i] = pid;
// 		cmdl = cmdl->next;
// 		i++;
// 	}

// 	// wait for all processes in parallel
// 	i = 0;
// 	while (i < npipe + 1)
// 	{
// 		waitpid(pids[i], NULL, 0);
// 		i++;
// 	}
    
// 	// free tbls
// 	i = 0;
// 	while (i < npipe)
// 		free(fd[i++]);
// 	free(fd);
// 	free(pids);
	
//     return (0);
// }

// https://github.com/tolmvad/pipex
// ============= V4 ==================

int	execute_pipes(t_sh *sh)
{
	int 		i;
	int 		n;
	int 		npipe;
	int 		pid;
	int 		*pids;
	int 		**fd;
	t_cmd_line	*cmdl;

	// count pipes
	npipe = 0;
	cmdl = sh->cmd_line_lst;
	cmdl = cmdl->next;
	while (cmdl)
	{
		npipe++;
		cmdl = cmdl->next;
	}

	cmdl = sh->cmd_line_lst;
	if (npipe == 0)
	{
		executor(cmdl, &sh->env);
		return (0);
	}

	// malloc tbls
	pids = malloc(sizeof(int) * (npipe + 1));
	if (!pids)
		return (-1);
	fd = malloc(sizeof(int *) * npipe);
	if (!fd)
		return (-1);
	i = 0;
	while (i < npipe)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return (-1);
		i++;
	}

	// instantiate pipes in tbl
	i = 0;
	while (i < npipe)
		if (pipe(fd[i++]) == -1)
			return (-1);

	// loop over commands
	i = 0;
	while (cmdl)
	{
		printf("Running cmd[%d]: %s\n", i, cmdl->cmd);
		pid = fork();
		if (pid < 0)
			return (-1);
		// child process
		if (pid == 0) 
		{
			// dup2
			if (i > 0)
				dup2(fd[i - 1][0], STDIN_FILENO);
			if (i < npipe)
				dup2(fd[i][1], STDOUT_FILENO);
			// close all pipes
			n = 0;
			while (n < npipe)
			{
				close(fd[n][0]);
				close(fd[n][1]);
				n++;
			}
			// exec
			executor(cmdl, &sh->env);
		}
		// parent process
		// close all pipes
		n = 0;
		while (n < npipe)
		{
			close(fd[n][0]);
			close(fd[n][1]);
			n++;
		}
		pids[i] = pid;
		cmdl = cmdl->next;
		i++;
	}

	// wait for all processes in parallel
	// waitpid(-1, NULL, 0);
	i = 0;
	while (i < npipe + 1)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
    
	// free tbls
	i = 0;
	while (i < npipe)
		free(fd[i++]);
	free(fd);
	free(pids);
	
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
		execute_cmds(&g_sh);
		// execute_pipes(&g_sh);
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
