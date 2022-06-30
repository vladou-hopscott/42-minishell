/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:18 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/30 14:30:19 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

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

void	exec_bin(t_cmd_line *cmdl, char **env)
{
	char	*cpy;

	cpy = ft_strdup(cmdl->cmd);
	if (access(cmdl->cmd, F_OK) != 0)
		cmd_pathfinder(&cmdl->cmd, env);
	if (cmdl->cmd)
	{
		free(cmdl->args[0]);
		cmdl->args[0] = ft_strdup(cmdl->cmd);
		execve(cmdl->cmd, cmdl->args, env);
	}
	else
	{
		err_cmd_not_found(&g_sh, cpy);
		free(cpy);
	}
}
