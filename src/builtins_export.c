/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:14 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 11:40:26 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

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

void	update_env(char *str, char **tbl, char ***penv)
{
	char	*key;
	char	*value;

	if (str[0] == '=')
		err_export_invalid(&g_sh, str);
	if (str[0] == '=')
		return ;
	key = ft_strdup(tbl[0]);
	if (key)
	{
		value = ft_strdup(tbl[1]);
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
	}
	free(key);
}

void	print_env(char **env, int fdout)
{
	int		i;
	char	**tbl;

	i = -1;
	while (env && env[++i])
	{
		ft_putstr_fd("export ", fdout);
		tbl = ft_split_export(env[i]);
		ft_putstr_fd(tbl[0], fdout);
		if (tbl && tbl[1])
		{
			ft_putstr_fd("=\"", fdout);
			if (ft_strncmp(tbl[1], " ", ft_strlen(" ") + 1) != 0)
				ft_putstr_fd(tbl[1], fdout);
			ft_putchar_fd('"', fdout);
		}
		ft_putstr_fd("\n", fdout);
		ft_freetbl(tbl, -1);
	}
}

char	**ft_split_export(char *str)
{
	int		i;
	char	**tbl;

	tbl = malloc(3 * sizeof(char *));
	if (!tbl)
		return (NULL);
	i = -1;
	while (str && str[++i])
		if (str[i] == '=')
			break ;
	tbl[0] = ft_strndup(str, i);
	tbl[1] = NULL;
	if (i != (int)ft_strlen(str))
		tbl[1] = ft_strdup(&str[i + 1]);
	tbl[2] = NULL;
	return (tbl);
}

void	builtin_export(int ac, char **av, char ***penv, int fdout)
{
	int		i;
	char	**tbl;

	i = 0;
	while (++i < ac)
	{
		tbl = ft_split_export(av[i]);
		if (tbl[0])
			update_env(av[i], tbl, penv);
		else
			err_export_invalid(&g_sh, av[i]);
		ft_freetbl(tbl, -1);
	}
	if (ac == 1)
		print_env(*penv, fdout);
	if (g_sh.has_pipe)
		ft_free_values_exit(&g_sh, SUCCESS, 1);
}
