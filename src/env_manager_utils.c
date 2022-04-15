/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:25:56 by swillis           #+#    #+#             */
/*   Updated: 2022/04/15 17:15:54 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tbllen(char **tbl)
{
	int	i;

	i = 0;
	while (tbl && tbl[i])
		i++;
	return (i + 1);
}

char	**tbl_append(char **tbl, char *str)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * (ft_tbllen(tbl) + 1));
	if (!new)
		return (tbl);
	i = 0;
	while (tbl && tbl[i])
	{
		new[i] = ft_strdup(tbl[i]);
		i++;
	}
	new[i++] = str;
	new[i] = NULL;
	ft_freetbl(tbl, -1);
	return (new);
}

int	env_findkeypos(char *key, char **env)
{
	char	**tbl;
	char	*str;
	int		i;

	i = 0;
	while (env && env[i])
	{
		tbl = ft_split(env[i], '=');
		str = tbl[0];
		if (ft_strncmp(str, key, ft_strlen(key)) == 0)
		{
			ft_freetbl(tbl, -1);
			return (i);
		}
		ft_freetbl(tbl, -1);
		i++;
	}
	return (-1);
}

char	**env_export(char *key, char *value, char **env)
{
	int		i;
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(key, "=");
	str = ft_strjoin(tmp, value);
	free(tmp);
	i = env_findkeypos(key, env);
	if (i == -1)
		env = tbl_append(env, str);
	else
	{
		free(env[i]);
		env[i] = str;
	}
	return (env);
}

char	*env_findkeyvalue(char *key, char **env)
{
	int		i;
	char	**tbl;
	char	*val;

	i = env_findkeypos(key, env);
	if (i == -1)
		return (NULL);
	tbl = ft_split(env[i], '=');
	val = ft_strdup(tbl[1]);
	ft_freetbl(tbl, -1);
	return (val);
}
