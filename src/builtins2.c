/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:14 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/21 21:15:11 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= EXPORT ====================================

int	is_valid_key(char *key)
{
	int	valid;
	int	i;

	if (key == NULL)
		return (0);
	valid = 0;
	if ((key[0] == '_') || ((key[0] >= 'A') && (key[0] <= 'Z')) \
	|| ((key[0] >= 'a') && (key[0] <= 'z')))
		valid = 1;
	i = 0;
	while (key && key[i])
	{
		if ((i + 1 < (int)ft_strlen(key)) && key[i] == '+')
			valid = 0;
		if ((i < (int)ft_strlen(key)) && key[i] == '-')
			valid = 0;
		i++;
	}
	if (valid == 0)
		return (0);
	if (key[i - 1] == '+')
		valid = 2;
	return (valid);
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

void	print_env(int ac, char **env, int fdout)
{
	int		i;
	char	**tbl;

	if (ac == 1)
	{
		i = 0;
		while (env && env[i])
		{
			ft_putstr_fd("export ", fdout);
			tbl = ft_split(env[i], '=');
			ft_putstr_fd(tbl[0], fdout);
			if (tbl[1] != NULL)
			{
				ft_putchar_fd('=', fdout);
				ft_putchar_fd('"', fdout);
				ft_putstr_fd(tbl[1], fdout);
				ft_putchar_fd('"', fdout);
			}
			ft_putchar_fd('\n', fdout);
			ft_freetbl(tbl, -1);
			i++;
		}
	}
	if (g_sh.has_pipe)
		exit(SUCCESS);
}

void	builtin_export(int ac, char **av, char ***penv, int fdout)
{
	int		i;
	char	**tbl;
	char	*key;
	char	*value;

	i = 0;
	while (++i < ac)
	{
		tbl = ft_split(av[i], '=');
		key = ft_strdup(tbl[0]);
		value = str_exportvalue(tbl);
		if (is_valid_key(key) == 1)
			*penv = env_export(key, value, (*penv));
		else if ((is_valid_key(key) == 2) && (value != NULL))
			*penv = env_export_append(key, value, (*penv));
		else
			err_export_invalid(&g_sh, key);
		if (value)
			free(value);
		free(key);
		ft_freetbl(tbl, -1);
	}
	print_env(ac, *penv, fdout);
}
