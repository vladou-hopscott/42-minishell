/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:57:15 by swillis           #+#    #+#             */
/*   Updated: 2022/04/08 16:25:31 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

// https://www.youtube.com/watch?v=6xbLgZpOBi8&ab_channel=CodeVault

// cmd type -a ls
// /usr/bin/ls -l /usr/bin/cat -e

int	main(int ac, char **av)
{
	int			fd[2];
	int			pid1;
	int			pid2;
	char		*path;
	char		*args;
	char		*env[] = {"HOME=/"};

	if (pipe(fd) < 0)
		return (1);
	// child process (first cmd)
	path = av[1];
	args = av[2];
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		// https://jameshfisher.com/2017/02/05/how-do-i-use-execve-in-c/
		execve(path, (char * const *)args, env);
	}
	// child process (second cmd)
	path = av[3];
	args = av[4];
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path, (char * const *)args, env);
	}
	// close ends and wait
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}