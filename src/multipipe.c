/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:12:24 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/28 13:55:29 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

void	close_fds(int fd1, int fd2)
{
	if (fd1 != STDIN_FILENO)
		close(fd1);
	if (fd2 != STDOUT_FILENO)
		close(fd2);
}

int	spawn_process(int fdin, int fdout, t_cmd_line *cmdl, t_sh *sh)
{
	pid_t	pid;

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
	close_fds(fdin, fdout);
	return (pid);
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
	if (fdin != STDIN_FILENO)
		close(fdin);
	if ((sh->cmd_line_lst)->next != NULL)
		close_fds(fd[1], fd[0]);
	cmdl = sh->cmd_line_lst;
	while (cmdl)
	{
		if ((0 < waitpid(cmdl->pid, &status, 0)) && (WIFEXITED(status)))
			set_error_exit_status(&g_sh, WEXITSTATUS(status));
		cmdl = cmdl->next;
	}
}
