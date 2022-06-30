/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:07 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/30 14:59:10 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= ECHO ====================================

int	find_first_arg_to_print(int ac, char **av, int *ntrail)
{
	int	i;
	int	j;

	i = 1;
	while ((i < ac) && (av[i][0] == '-'))
	{
		j = 1;
		while (av[i][j] == 'n')
			j++;
		if (j != (int)ft_strlen(av[i]))
			break ;
		*ntrail = 0;
		i++;
	}
	return (i);
}

void	builtin_echo(int ac, char **av, int fdout)
{
	int	i;
	int	ntrail;

	ntrail = 1;
	i = find_first_arg_to_print(ac, av, &ntrail);
	if (i < ac)
		ft_putstr_fd(av[i++], fdout);
	while (i < ac)
	{
		ft_putchar_fd(' ', fdout);
		ft_putstr_fd(av[i++], fdout);
	}
	if (ntrail)
		ft_putchar_fd('\n', fdout);
	exit(SUCCESS);
}

// ======================= PWD ====================================

void	builtin_pwd(int ac, int fdout)
{
	char	*pwd;
	char	*buf;

	if (ac == 1)
	{
		buf = getcwd(NULL, 0);
		pwd = ft_strdup(buf);
		free(buf);
		ft_putstr_fd(pwd, fdout);
		ft_putchar_fd('\n', fdout);
		free(pwd);
		exit(SUCCESS);
	}
	else
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		exit(FAILURE);
	}
}

// ======================= CD ====================================

void	builtin_cd(int ac, char **av, char ***penv)
{
	char	*path;
	char	*newpath;

	if (ac != 2)
	{
		ft_putstr_fd("command cd only accepts relative or absolute paths\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		return ;
	}
	if (!g_sh.has_pipe)
	{
		path = getcwd(NULL, 999999);
		*penv = env_export("OLDPWD", path, *penv);
		free(path);
		if (chdir(av[1]) == -1)
		{
			perror(av[1]);
			set_error_exit_status(&g_sh, FAILURE);
			return ;
		}
		newpath = getcwd(NULL, 999999);
		if (env_findkeypos("PWD", *penv) != -1)
			*penv = env_export("PWD", newpath, *penv);
		free(newpath);
	}
}

// ======================= EXIT ====================================

void	builtin_exit(int ac, char **av)
{
	if (ac > 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
	}
	else if (!g_sh.has_pipe)
	{
		if (ac == 1)
			exit(0);
		else if (ac == 2)
			exit(ft_atoi(av[1]));
		exit(FAILURE);
	}
}
