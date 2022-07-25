/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:12:24 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 13:58:03 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

void	close_fds(int fdin, int fdout)
{
	if (fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
}

int	check_fork(t_cmd_line *cmdl, char **env)
{
	if (g_sh.has_pipe)
		return (SUCCESS);
	if (cmdl->cmd[0] == '\0')
		return (FAILURE);
	if (ft_strncmp(cmdl->cmd, "echo", ft_strlen("echo") + 1) == 0)
		return (SUCCESS);
	else if (ft_strncmp(cmdl->cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		return (SUCCESS);
	else if (ft_strncmp(cmdl->cmd, "env", ft_strlen("env") + 1) == 0)
		return (SUCCESS);
	else
		return (check_exec_bin(cmdl, env));
	return (FAILURE);
}

void	dup_and_close_fds(int fdin, int fdout, t_cmd_line *cmdl)
{
	if (cmdl->fdin != STDIN_FILENO)
	{
		dup2(cmdl->fdin, STDIN_FILENO);
		close(cmdl->fdin);
		if (fdin != STDIN_FILENO)
			close(fdin);
	}
	else if (fdin != STDIN_FILENO)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (cmdl->fdout != STDOUT_FILENO)
	{
		dup2(cmdl->fdout, STDOUT_FILENO);
		close(cmdl->fdout);
		if (fdout != STDOUT_FILENO)
			close(fdout);
	}
	else if ((fdout != STDOUT_FILENO) && (cmdl->next != NULL))
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
}

void	spawn_process(int fdin, int *fd, t_cmd_line *cmdl, t_sh *sh)
{
	int		fdout;

	fdout = cmdl->fdout;
	if (check_fork(cmdl, sh->env) == SUCCESS)
	{
		signal(SIGINT, SIG_IGN);
		cmdl->pid = fork();
		if (cmdl->pid < 0)
			set_error_exit_status(&g_sh, MAJOR_FAILURE);
		if (cmdl->pid == 0)
		{
			handle_signals(1);
			if (fd != NULL)
			{
				close(fd[0]);
				fdout = fd[1];
			}
			dup_and_close_fds(fdin, fdout, cmdl);
			executor(cmdl, &sh->env);
			return ;
		}
	}
	else
		executor(cmdl, &sh->env);
	close_fds(fdin, fdout);
}

void	execute_pipes(t_sh *sh)
{
	int			status;
	int			fdin;
	t_cmd_line	*cmdl;

	status = 0;
	cmdl = sh->cmd_line_lst;
	fdin = cmdl->fdin;
	while (cmdl->next)
	{
		sh->has_pipe = 1;
		pipe(cmdl->fd);
		if (cmdl->cmd)
			spawn_process(fdin, cmdl->fd, cmdl, sh);
		close(cmdl->fd[1]);
		fdin = cmdl->fd[0];
		cmdl = cmdl->next;
	}
	if (cmdl->cmd)
		spawn_process(fdin, NULL, cmdl, sh);
	cmdl = sh->cmd_line_lst;
	while (cmdl)
	{
		wait_child(cmdl, status, sh);
		cmdl = cmdl->next;
	}
}
