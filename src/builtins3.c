/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scottwillis <scottwillis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:07:49 by vladimir          #+#    #+#             */
/*   Updated: 2022/07/21 10:59:56 by scottwillis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= CD ====================================

void	execute_cd(char **av, char ***penv)
{
	char	*path;
	char	*newpath;

	path = getcwd(NULL, 999999);
	if (!path)
	{
		ft_putstr_fd("chdir: error retrieving current directory\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		if (g_sh.has_pipe)
			exit(FAILURE);
		return ;
	}
	*penv = env_export("OLDPWD", path, *penv);
	free(path);
	if (chdir(av[1]) == -1)
	{
		perror(av[1]);
		set_error_exit_status(&g_sh, FAILURE);
		if (g_sh.has_pipe)
			exit(FAILURE);
		return ;
	}
	newpath = getcwd(NULL, 999999);
	if (env_findkeypos("PWD", *penv) != -1)
		*penv = env_export("PWD", newpath, *penv);
	free(newpath);
}

void	builtin_cd(int ac, char **av, char ***penv)
{
	if (ac != 2)
	{
		ft_putstr_fd("command cd only accepts relative or absolute paths\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		if (g_sh.has_pipe)
			exit(FAILURE);
		return ;
	}
	execute_cd(av, penv);
}

// ======================= ENV ====================================

void	builtin_env(int ac, char **env, int fdout)
{
	int	i;

	if (ac == 1)
	{
		i = 0;
		while (env && env[i])
		{
			ft_putstr_fd(env[i], fdout);
			ft_putchar_fd('\n', fdout);
			i++;
		}
		exit(SUCCESS);
	}
	else
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		exit(FAILURE);
	}
}
