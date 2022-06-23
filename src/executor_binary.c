/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:18 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/23 11:37:19 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= BIN ====================================

void	update_stdin_stdout(int *cpy_stdin, int *cpy_stdout, t_cmd_line *cmdl)
{
	*cpy_stdin = dup(0);
	*cpy_stdout = dup(1);
	dup2(cmdl->fdin, 0);
	dup2(cmdl->fdout, 1);
}

void	reset_stdin_stdout(int cpy_stdin, int cpy_stdout, t_cmd_line *cmdl)
{
	dup2(cpy_stdin, 0);
	dup2(cpy_stdout, 1);
	close(cpy_stdin);
	close(cpy_stdout);
	if (cmdl->fdin != 0)
		close(cmdl->fdin);
	if (cmdl->fdout != 1)
		close(cmdl->fdout);
}

int	process_cmd(t_cmd_line *cmdl, char **env)
{
	int		pid;
	int		cpy_stdin;
	int		cpy_stdout;
	int		status;

	update_stdin_stdout(&cpy_stdin, &cpy_stdout, cmdl);
	free(cmdl->args[0]);
	cmdl->args[0] = ft_strdup(cmdl->cmd);
	pid = fork();
	if (pid < 0)
	{
		set_error_exit_status(&g_sh, MAJOR_FAILURE);
		reset_stdin_stdout(cpy_stdin, cpy_stdout, cmdl);
		return (1);
	}
	if (pid == 0)
		execve(cmdl->cmd, cmdl->args, env);
	if ((0 < waitpid(pid, &status, 0)) && (WIFEXITED(status)))
		set_error_exit_status(&g_sh, WEXITSTATUS(status));
	close(pid);
	reset_stdin_stdout(cpy_stdin, cpy_stdout, cmdl);
	return (0);
}

void	exec_bin(t_cmd_line *cmdl, char **env)
{
	char	*cpy;

	cpy = ft_strdup(cmdl->cmd);
	if (access(cmdl->cmd, F_OK) != 0)
		cmd_pathfinder(&cmdl->cmd, env);
	if (cmdl->cmd)
		process_cmd(cmdl, env);
	else
	{
		err_cmd_not_found(&g_sh, cpy);
		free(cpy);
	}
}
