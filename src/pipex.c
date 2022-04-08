/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:57:15 by swillis           #+#    #+#             */
/*   Updated: 2022/04/08 18:33:59 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

// https://stackoverflow.com/questions/7656549/understanding-requirements-for-execve-and-setting-environment-vars

// char *argv[] = { "/bin/sh", "-c", "env", 0 };

// char	*env[] =
// {
// 	"HOME=/",
// 	"PATH=/bin:/usr/bin",
// 	"TZ=UTC0",
// 	"USER=beelzebub",
// 	"LOGNAME=tarzan",
// 	0
// };

// https://jameshfisher.com/2017/02/05/how-do-i-use-execve-in-c/
// https://www.youtube.com/watch?v=6xbLgZpOBi8&ab_channel=CodeVault

// cmd type -a ls
// /usr/bin/ls -l /usr/bin/cat -e

// Access types
// 	R_OK	4		/* Test for read permission.  */
// 	W_OK	2		/* Test for write permission.  */
// 	X_OK	1		/* Test for execute permission.  */
// 	F_OK	0		/* Test for existence.  */

// http://codewiki.wikidot.com/c:system-calls:open

char	*g_env;

typedef struct s_pvars {
	int			fd[2];
	int			file1;
	int			file2;
	int			pid1;
	int			pid2;
	char		*path;
	char		*args;
}				t_pvars;

int	close_fds(int file1, int file2)
{
	close(file1);
	close(file2);
	return (1);
}

int	init_pvars(t_pvars pv, char **av)
{
	if (pipe(pv.fd) < 0)
		return (1);
	pv.file1 = open(av[1], O_RDWR);
	if (pv.file1 < 0)
		return (1);
	pv.file2 = open(av[4], O_RDWR);
	if (pv.file2 < 0)
	{
		close(pv.file1);
		return (1);
	}
	pv.pid1 = fork();
	if (pv.pid1 < 0)
		return (close_fds(pv.file1, pv.file2));
	pv.pid2 = fork();
	if (pv.pid2 < 0)
		return (close_fds(pv.file1, pv.file2));
}

int	run_children(t_pvars pv)
{
	if (pv.pid1 == 0)
	{
		dup2(pv.file1, STDIN_FILENO);
		dup2(pv.fd[1], STDOUT_FILENO);
		close_fds(pv.fd[0], pv.fd[1]);
		if (access(pv.path, F_OK) && access(pv.path, R_OK) && access(pv.path, W_OK))
			execve(pv.path, pv.args, g_env);
		else
			return (close_fds(pv.file1, pv.file2));
	}
	if (pv.pid2 == 0)
	{
		dup2(pv.fd[0], STDIN_FILENO);
		dup2(pv.file2, STDOUT_FILENO);
		close_fds(pv.fd[0], pv.fd[1]);
		if (access(pv.path, F_OK) && access(pv.path, R_OK) && access(pv.path, W_OK))
			execve(pv.path, pv.args, g_env);
		else
			return (close_fds(pv.file1, pv.file2));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_pvars	pv;

	if (ac != 5)
		return (1);
	if (init_pvars(pv, av))
		return (1);
	if (run_children(pv))
		return (1);
	close_fds(pv.fd[0], pv.fd[1]);
	waitpid(pv.pid1, NULL, 0);
	waitpid(pv.pid2, NULL, 0);
	return (0);
}