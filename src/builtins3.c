/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:07:49 by vladimir          #+#    #+#             */
/*   Updated: 2022/07/23 19:46:46 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= CD ====================================

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

// ======================= ENV ====================================

void	builtin_env(int ac, char **env, int fdout)
{
	int		i;
	char	**tbl;

	if (ac == 1)
	{
		i = 0;
		while (env && env[i])
		{
			tbl = ft_split(env[i], '=');
			if (tbl[1] != NULL)
			{
				ft_putstr_fd(env[i], fdout);
				ft_putchar_fd('\n', fdout);
			}
			ft_freetbl(tbl, -1);
			i++;
		}
		ft_free_values_exit(&g_sh, SUCCESS, 1);
	}
	else
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		ft_free_values_exit(&g_sh, FAILURE, 1);
	}
}
