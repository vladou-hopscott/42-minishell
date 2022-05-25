/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:45:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/25 18:41:34 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	run_children(char *delimitor)
//{
//	int	pid;

//	pid = fork();
//	printf("pid=%d\n", pid);
//	printf("delimitor=%s\n", delimitor);
//	if (pid < 0)
//	{
//		printf("ERROR PID\n");
//		return (1);
//	}

//	//if (pv->pid2 == 0)
//	//{
//	//	dup2(pv->fd[0], STDIN_FILENO);
//	//	dup2(pv->file2, STDOUT_FILENO);
//	//	close_fds(pv->fd[0], pv->fd[1]);
//	//	execve(pv->path2, pv->args2, environ);
//	//}
//	//close_fds(pv->fd[0], pv->fd[1]);
//	waitpid(pid, NULL, 0);
//	//close_fds(pv->file1, pv->file2);
//	return (0);
//}



//A RAJOUTER : GESTION DES QUOTES ET DES EXPANDS
int	run_children(char *delimitor)
{
	char	*tmp;
	int		fd_tmp;

	fd_tmp = open("heredoc", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	while (1)
	{
		tmp = readline("> ");
		if (!ft_strncmp(tmp, delimitor, ft_strlen(delimitor)) && ft_strlen(tmp) == ft_strlen(delimitor))
		{
			close(fd_tmp);
			break;
		}
		ft_putstr_fd("\n", fd_tmp);
		ft_putstr_fd(tmp, fd_tmp);
	}
	return (0);
}

int	heredoc(char *delimitor)
{
	run_children(delimitor);
	return (0);
}
