/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:35:53 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/21 21:16:00 by swillis          ###   ########.fr       */
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
		if (ft_strncmp(str, key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(str))
		{
			ft_freetbl(tbl, -1);
			return (i);
		}
		ft_freetbl(tbl, -1);
		i++;
	}
	return (-1);
}

char	*env_export_append_utils(char *tmp, char *envi, char *value)
{
	char	**tbl;
	char	*nvalue;
	char	*str;

	tbl = ft_split(envi, '=');
	nvalue = ft_strjoin(tbl[1], value);
	ft_freetbl(tbl, -1);
	str = ft_strjoin(tmp, nvalue);
	free(nvalue);
	return (str);
}

char	**env_export_append(char *key, char *value, char **env)
{
	int		i;
	char	*nkey;
	char	*tmp;
	char	*str;

	nkey = ft_strndup(key, ft_strlen(key) - 1);
	tmp = ft_strjoin(nkey, "=");
	i = env_findkeypos(nkey, env);
	if (i == -1)
	{
		str = ft_strjoin(tmp, value);
		env = tbl_append(env, str);
	}
	else
	{
		str = env_export_append_utils(tmp, env[i], value);
		free(env[i]);
		env[i] = str;
	}
	free(nkey);
	free(tmp);
	return (env);
}
