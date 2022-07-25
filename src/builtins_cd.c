/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:07:49 by vladimir          #+#    #+#             */
/*   Updated: 2022/07/25 11:48:20 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

void	execute_cd(char **av, char ***penv, char *path)
{
	char	*newpath;

	*penv = env_export("OLDPWD", path, *penv);
	free(path);
	if (chdir(av[1]) == -1)
	{
		perror(av[1]);
		set_error_exit_status(&g_sh, FAILURE);
		if (g_sh.has_pipe)
			ft_free_values_exit(&g_sh, FAILURE, 1);
		return ;
	}
	newpath = getcwd(NULL, 999999);
	if (env_findkeypos("PWD", *penv) != -1)
		*penv = env_export("PWD", newpath, *penv);
	free(newpath);
}

void	builtin_cd(int ac, char **av, char ***penv)
{
	char	*path;

	if (ac != 2)
	{
		ft_putstr_fd("command cd only accepts relative or absolute paths\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		if (g_sh.has_pipe)
			ft_free_values_exit(&g_sh, FAILURE, 1);
		return ;
	}
	path = getcwd(NULL, 999999);
	if (!path)
	{
		ft_putstr_fd("chdir: error retrieving current directory\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		if (g_sh.has_pipe)
			ft_free_values_exit(&g_sh, FAILURE, 1);
		return ;
	}
	execute_cd(av, penv, path);
	if (g_sh.has_pipe)
		ft_free_values_exit(&g_sh, SUCCESS, 1);
}
