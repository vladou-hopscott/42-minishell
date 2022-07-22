/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:14 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/22 12:08:35 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= EXPORT ====================================
int	is_valid_key(char *key, char *str, char *value)
{
	int	valid;
	int	i;

	valid = 0;
	if ((key[0] == '_') || ((key[0] >= 'A') && (key[0] <= 'Z')) \
	|| ((key[0] >= 'a') && (key[0] <= 'z')))
		valid = 1;
	i = -1;
	while (key && key[++i])
	{
		if ((i + 1 < (int)ft_strlen(key)) && key[i] == '+')
			return (0);
		if ((i < (int)ft_strlen(key)) && key[i] == '-')
			return (0);
	}
	if (key[i - 1] == '+')
	{
		valid = 2;
		if ((str[i] == '=') && (value == NULL))
			valid = 3;
	}
	else if ((str[i] == '=') && (value == NULL))
		valid = 4;
	return (valid);
}

char	*str_exportvalue(char **tbl)
{
	int		i;
	char	*value;

	value = NULL;
	if (tbl && tbl[1])
	{
		value = ft_strdup(tbl[1]);
		i = 2;
		while (tbl && tbl[i])
		{
			value = ft_strjoin(value, tbl[i]);
			i++;
		}
	}
	return (value);
}

void	print_env(int ac, char **env, int fdout)
{
	int		i;
	char	**tbl;

	if (ac == 1)
	{
		i = -1;
		while (env && env[++i])
		{
			ft_putstr_fd("export ", fdout);
			tbl = ft_split(env[i], '=');
			ft_putstr_fd(tbl[0], fdout);
			if (tbl[1] != NULL)
			{
				ft_putchar_fd('=', fdout);
				ft_putchar_fd('"', fdout);
				if (ft_strncmp(tbl[1], " ", ft_strlen(" ") + 1) != 0)
					ft_putstr_fd(tbl[1], fdout);
				ft_putchar_fd('"', fdout);
			}
			ft_putchar_fd('\n', fdout);
			ft_freetbl(tbl, -1);
		}
	}
	if (g_sh.has_pipe)
		exit(SUCCESS);
}

void	update_env(char *str, char **tbl, char ***penv)
{
	char	*key;
	char	*value;

	key = ft_strdup(tbl[0]);
	if (!key)
		return ;
	value = str_exportvalue(tbl);
	if (is_valid_key(key, str, value) == 0)
		err_export_invalid(&g_sh, key);
	else if (is_valid_key(key, str, value) == 1)
		*penv = env_export(key, value, (*penv));
	else if (is_valid_key(key, str, value) == 2)
		*penv = env_export_append(key, value, (*penv));
	else if (is_valid_key(key, str, value) == 3)
		*penv = env_export_append(key, " ", (*penv));
	else if (is_valid_key(key, str, value) == 4)
		*penv = env_export(key, " ", (*penv));
	if (value)
		free(value);
	free(key);
}

void	builtin_export(int ac, char **av, char ***penv, int fdout)
{
	int		i;
	char	**tbl;

	i = 0;
	while (++i < ac)
	{
		tbl = ft_split(av[i], '=');
		if (tbl[0])
			update_env(av[i], tbl, penv);
		else
			err_export_invalid(&g_sh, av[i]);
		ft_freetbl(tbl, -1);
	}
	print_env(ac, *penv, fdout);
}
