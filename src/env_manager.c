/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:33:14 by swillis           #+#    #+#             */
/*   Updated: 2022/04/13 17:57:12 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_environment(void)
{
	char	**env;

	env = malloc(sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = NULL;
	return (env);
}

int	env_findkeypos(char *key, char **env)
{
	char	**tbl;
	char	*str;
	int		i;

	i = 0;
	while (env && env[i])
	{
		tbl = ft_split(env[i], "=");
		str = tbl[0];
		ft_freetbl(tbl, -1);
		if (ft_strncmp(str, key, ft_strlen(key)) == 0)
		{
			free(str);
			return (i);
		}
		i++;
	}
	free(str);
	return (-1);
}

void	env_export(char *key, char *value, char **env)
{
	int		i;
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(key, "=");
	str = ft_strjoin(tmp, value);
	i = env_findkeypos(key, env);
	if (i >= 0)
	{
		free(env[i]);
		env[i] = str;
	}
	else
	{
		i = 0;
		while (env && env[i])
	}
}

void	env_getcwd(char **env)
{
	char	*buf;
	char	*cwd;

	buf = getcwd(NULL, 0);
	cwd = ft_strdup(buf);
	env_export("CWD", cwd, env);
}