/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:35:57 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/22 11:26:26 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**env_export(char *key, char *value, char **env)
{
	int		i;
	char	*tmp;
	char	*str;

	if (value != NULL)
	{
		tmp = ft_strjoin(key, "=");
		str = ft_strjoin(tmp, value);
		free(tmp);
	}
	else
		str = ft_strdup(key);
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

char	**env_getcwd(char **env)
{
	char	*buf;
	char	*cwd;

	buf = getcwd(NULL, 0);
	cwd = ft_strdup(buf);
	free(buf);
	env = env_export("PWD", cwd, env);
	free(cwd);
	return (env);
}

char	**env_getpath(char **env)
{
	char	*path;
	char	*cwd;

	cwd = env_findkeyvalue("PWD", env);
	path = ft_strjoin(cwd, "/bin");
	free(cwd);
	env = env_export("PATH", path, env);
	free(path);
	return (env);
}

char	**copy_environment(char **env)
{
	char	**env_cpy;
	int		i;

	env_cpy = ft_calloc(ft_str_tbl_len(env) + 1, sizeof(char *));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (i < ft_str_tbl_len(env))
	{
		env_cpy[i] = ft_strdup(env[i]);
		if (!env_cpy[i])
			return (ft_freetbl(env_cpy, i));
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}
