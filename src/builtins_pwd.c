/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:07 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 11:40:48 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

void	builtin_pwd(int ac, int fdout)
{
	char	*pwd;
	char	*buf;
	char	*err1;
	char	*err2;
	char	*err3;

	(void)ac;
	err1 = "pwd: error retrieving current directory: getcwd: ";
	err2 = "cannot access parent directories: No such file or directory\n";
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		err3 = ft_strjoin(err1, err2);
		ft_putstr_fd(err3, 2);
		set_error_exit_status(&g_sh, FAILURE);
		free(err3);
		ft_free_values_exit(&g_sh, FAILURE, 1);
	}
	pwd = ft_strdup(buf);
	free(buf);
	ft_putstr_fd(pwd, fdout);
	ft_putchar_fd('\n', fdout);
	free(pwd);
	ft_free_values_exit(&g_sh, SUCCESS, 1);
}
