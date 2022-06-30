/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:12:24 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/30 14:04:57 by vladimir         ###   ########.fr       */
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

int	spawn_process(int fdin, int *fd, t_cmd_line *cmdl, t_sh *sh)
{
	pid_t	pid;
	int		fdout;

	pid = -1;
	fdout = cmdl->fdout;
	if (check_fork(cmdl, sh->env) == SUCCESS)
	{
		pid = fork();
		if (pid < 0)
			set_error_exit_status(&g_sh, MAJOR_FAILURE);
		if (pid == 0)
		{
			if (fd != NULL)
			{
				close(fd[0]);
				fdout = fd[1];
			}
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
	}
	else
		executor(cmdl, &sh->env);
	close_fds(fdin, fdout);
	return (pid);
}

void	execute_pipes(t_sh *sh)
{
	int 		status;
	int 		fdin;
	t_cmd_line	*cmdl;

	cmdl = sh->cmd_line_lst;
	fdin = cmdl->fdin;
	while (cmdl->next)
	{
		sh->has_pipe = 1;
		pipe(cmdl->fd);
		cmdl->pid = spawn_process(fdin, cmdl->fd, cmdl, sh);
		close(cmdl->fd[1]);
		fdin = cmdl->fd[0];
		cmdl = cmdl->next;
	}

	cmdl->pid = spawn_process(fdin, NULL, cmdl, sh);
	
	// cmdl = sh->cmd_line_lst;
	// while (cmdl)
	// {
	// 	close_fds(cmdl->fd[0], cmdl->fd[1]);
	// 	cmdl = cmdl->next;
	// }
	// if ((sh->cmd_line_lst)->next != NULL)
	// 	close_fds(cmdl->fd[0], cmdl->fd[1]);

	cmdl = sh->cmd_line_lst;
	while (cmdl)
	{
		if (cmdl->pid != -1)
			if ((0 < waitpid(cmdl->pid, &status, 0)) && (WIFEXITED(status)))
				set_error_exit_status(&g_sh, WEXITSTATUS(status));
		cmdl = cmdl->next;
	}
}
