/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:57:15 by swillis           #+#    #+#             */
/*   Updated: 2022/06/09 15:39:58 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ;

int	init_pvars(t_pvars *pv, char **av)
{
	if (pipe(pv->fd) < 0)
		return (1);
	pv->file1 = open(av[1], O_RDONLY);
	if (pv->file1 < 0)
		return (1);
	pv->file2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC);
	if (pv->file2 < 0)
	{
		close(pv->file1);
		return (1);
	}
	pv->cmd1 = cmd_strfinder(av[2]);
	pv->cmd2 = cmd_strfinder(av[3]);
	pv->env_path = env_pathfinder(environ);
	pv->path1 = cmd_pathfinder(pv->cmd1, pv->env_path);
	pv->path2 = cmd_pathfinder(pv->cmd2, pv->env_path);
	pv->args1 = cmd_argstbl(av[2], pv->cmd1);
	pv->args2 = cmd_argstbl(av[3], pv->cmd2);
	return (0);
}

int	run_children(t_pvars *pv)
{
	pv->pid1 = fork();
	if (pv->pid1 < 0)
		return (1);
	if (pv->pid1 == 0)
	{
		dup2(pv->file1, STDIN_FILENO);
		dup2(pv->fd[1], STDOUT_FILENO);
		close_fds(pv->fd[0], pv->fd[1]);
		execve(pv->path1, pv->args1, environ);
	}
	pv->pid2 = fork();
	if (pv->pid2 < 0)
		return (1);
	if (pv->pid2 == 0)
	{
		dup2(pv->fd[0], STDIN_FILENO);
		dup2(pv->file2, STDOUT_FILENO);
		close_fds(pv->fd[0], pv->fd[1]);
		execve(pv->path2, pv->args2, environ);
	}
	close_fds(pv->fd[0], pv->fd[1]);
	waitpid(pv->pid1, NULL, 0);
	waitpid(pv->pid2, NULL, 0);
	close_fds(pv->file1, pv->file2);
	// while (wait(NULL) != -1)
	// 	;
	return (0);
}

int	free_pvars(t_pvars *pv)
{
	if (pv->cmd1)
		free(pv->cmd1);
	if (pv->cmd2)
		free(pv->cmd2);
	if (pv->env_path)
		free(pv->env_path);
	if (pv->path1)
		free(pv->path1);
	if (pv->path2)
		free(pv->path2);
	if (pv->args1)
		ft_freetbl(pv->args1, -1);
	if (pv->args2)
		ft_freetbl(pv->args2, -1);
	free(pv);
	return (1);
}

int	main(int ac, char **av)
{
	t_pvars	*pv;

	if (ac == 5)
	{
		pv = malloc(sizeof(t_pvars));
		if (!pv)
			return (1);
		if (init_pvars(pv, av))
			return (free_pvars(pv));
		if ((pv->path1 && pv->args1) && \
					(pv->path2 && pv->args2))
			if (run_children(pv))
				return (free_pvars(pv));
		free_pvars(pv);
	}
	return (0);
}
