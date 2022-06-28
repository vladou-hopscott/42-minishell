/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:29:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/28 12:08:48 by vnafissi         ###   ########.fr       */
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

// ==================================

// void	execute_cmds(t_sh *sh)
// {
// 	t_cmd_line	*cmdl;

// 	cmdl = sh->cmd_line_lst;
// 	while (cmdl)
// 	{
// 		executor(cmdl, &sh->env);
// 		cmdl = cmdl->next;
// 	}
// }

// ==================================

// http://web.cse.ohio-state.edu/~mamrak.1/CIS762/pipes_lab_notes.html

// int	execute_pipes(t_cmdl **lst, char **env, int fdin, int fdout)
// {
// 	int 	i;
// 	int 	n;
// 	int 	npipe;
// 	int 	pid;
// 	int 	*pids;
// 	int 	**fd;
// 	t_cmdl	*cmdl;

// 	// count pipes
// 	npipe = 0;
// 	cmdl = *lst;
// 	cmdl = cmdl->next;
// 	while (cmdl)
// 	{
// 		npipe++;
// 		cmdl = cmdl->next;
// 	}

// 	// if single cmd
// 	cmdl = *lst;
// 	if (npipe == 0)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 			return (-1);
// 		if (pid == 0)
// 			execve(cmdl->cmd, cmdl->args, env);
// 		wait(NULL);
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
// 	while (cmdl)
// 	{
// 		// printf("Running cmd[%d]: %s\n", i, cmdl->cmd);
// 		pid = fork();
// 		if (pid < 0)
// 			return (-1);
// 		// child process
// 		if (pid == 0)
// 		{
// 			// dups
// 			if (i == 0)
// 				dup2(fdin, STDIN_FILENO);
// 			if (i > 0)
// 				dup2(fd[i - 1][0], STDIN_FILENO);
// 			if (i < npipe - 1)
// 				dup2(fd[i][1], STDOUT_FILENO);
// 			if (i == npipe - 1)
// 				dup2(fdout, STDOUT_FILENO);
// 			// close all pipes
// 			n = 0;
// 			while (n < npipe)
// 			{
// 				close(fd[n][0]);
// 				close(fd[n][1]);
// 				n++;
// 			}
// 			// exec
// 			execve(cmdl->cmd, cmdl->args, env);
// 		}
// 		pids[i] = pid;
// 		cmdl = cmdl->next;
// 		i++;
// 	}

// 	// parent process
// 	// close all pipes
// 	n = 0;
// 	while (n < npipe)
// 	{
// 		close(fd[n][0]);
// 		close(fd[n][1]);
// 		n++;
// 	}

// 	// wait for all processes in parallel
// 	// waitpid(-1, NULL, 0);
// 	while (wait(NULL) != -1)
// 		;
// 	// i = 0;
// 	// while (i < npipe + 1)
// 	// {
// 	// 	waitpid(pids[i], NULL, 0);
// 	// 	i++;
// 	// }

// 	// free tbls
// 	i = 0;
// 	while (i < npipe)
// 		free(fd[i++]);
// 	free(fd);
// 	free(pids);

//     return (0);
// }

// ==================================

// ============= MULTIPIPE ==========================================
// https://stackoverflow.com/questions/8082932/connecting-n-commands-with-pipes-in-a-shell?answertab=trending#tab-top
// ==================================================================
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
		if ((fdout != STDOUT_FILENO) && (cmdl->next != NULL))
		{
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
		executor(cmdl, &sh->env);
		return (0);
	}
	return (pid);
}


//void	execute_pipes(t_sh *sh)
//{
//	int 		i;
//	int 		n;
//	int 		status;
//	int 		fdin;
//	int			fd[2];
//	t_cmd_line	*cmdl;

//	//cmdl = sh->cmd_line_lst;;
//	//cmdl = cmdl->next;
//	//n = 0;
//	//while (cmdl)
//	//{
//	//	n++;
//	//	cmdl = cmdl->next;
//	//}
//	cmdl = sh->cmd_line_lst;
//	fdin = cmdl->fdin;
//	i = 0;
//	while (i < n)
//	{
//		pipe(fd);
//		cmdl->pid = spawn_process(fdin, fd[1], cmdl, sh);
//		close(fd[1]);
//		fdin = fd[0];
//		cmdl = cmdl->next;
//		i++;
//	}
//	cmdl->pid = spawn_process(fdin, cmdl->fdout, cmdl, sh);
//	//if (n > 0)
//	//{
//	//	close(fd[0]);
//	//	close(fd[1]);
//	//}
//	cmdl = sh->cmd_line_lst;
//	while (cmdl)
//	{
//		if ((0 < waitpid(cmdl->pid, &status, 0)) && (WIFEXITED(status)))
//			set_error_exit_status(&g_sh, WEXITSTATUS(status));
//		cmdl = cmdl->next;
//	}
//}

void	close_fds(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	execute_pipes(t_sh *sh)
{
	int 		status;
	int 		fdin;
	int			fd[2];
	t_cmd_line	*cmdl;

	cmdl = sh->cmd_line_lst;
	fdin = cmdl->fdin;
	while (cmdl->next)
	{
		pipe(fd);
		cmdl->pid = spawn_process(fdin, fd[1], cmdl, sh);
		close(fd[1]);
		fdin = fd[0];
		cmdl = cmdl->next;
	}
	cmdl->pid = spawn_process(fdin, cmdl->fdout, cmdl, sh);
	if ((sh->cmd_line_lst)->next != NULL)
		close_fds(fd[0], fd[1]);
	cmdl = sh->cmd_line_lst;
	while (cmdl)
	{
		if ((0 < waitpid(cmdl->pid, &status, 0)) && (WIFEXITED(status)))
			set_error_exit_status(&g_sh, WEXITSTATUS(status));
		cmdl = cmdl->next;
	}
}

// ======================================

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
