/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scottwillis <scottwillis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:14 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/15 16:14:09 by scottwillis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= EXPORT ====================================

int	is_valid_key(char *key)
{
	if (key[0] == '_')
		return (1);
	if ((key[0] >= 'A') && (key[0] <= 'Z'))
		return (1);
	if ((key[0] >= 'a') && (key[0] <= 'z'))
		return (1);
	return (0);
}

char	*str_exportvalue(char **tbl)
{
	int		i;
	char	*value;

	if (tbl[1] == NULL)
		return (NULL);
	value = ft_strdup(tbl[1]);
	i = 2;
	while (tbl && tbl[i])
	{
		value = ft_strjoin(value, tbl[i]);
		i++;
	}
	return (value);
}

void	builtin_export(int ac, char **av, char ***penv)
{
	int		i;
	char	**env;
	char	**tbl;
	char	*key;
	char	*value;

	i = 1;
	if (!g_sh.has_pipe)
	{
		while (i < ac)
		{
			env = *penv;
			tbl = ft_split(av[i], '=');
			key = ft_strdup(tbl[0]);
			if (is_valid_key(key))
			{
				value = str_exportvalue(tbl);
				*penv = env_export(key, value, env);
				free(value);
			}
			else
				err_export_invalid(&g_sh, key);
			free(key);
			ft_freetbl(tbl, -1);
			i++;
		}
	}
}

// ======================= UNSET ====================================

void	tbl_remove(char ***ptr, char *key)
{
	int		i;
	int		j;
	int		pos;
	char	**tbl;
	char	**new;

	tbl = *ptr;
	pos = env_findkeypos(key, tbl);
	if (pos != -1)
		return ;
	new = malloc(sizeof(char *) * (ft_tbllen(tbl) - 1));
	if (!new)
		return ;
	i = 0;
	j = 0;
	while (tbl && tbl[i])
	{
		if (i == pos)
			i++;
		else
			new[j++] = ft_strdup(tbl[i++]);
	}
	new[j] = NULL;
	*ptr = new;
	ft_freetbl(tbl, -1);
}

void	builtin_unset(int ac, char **av, char ***penv)
{
	int		i;

	i = 1;
	if (!g_sh.has_pipe)
	{
		while (i < ac)
		{
			tbl_remove(penv, av[i]);
			i++;
		}
	}
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
