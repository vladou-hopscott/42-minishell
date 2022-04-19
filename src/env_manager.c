/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:25:56 by swillis           #+#    #+#             */
/*   Updated: 2022/04/15 21:32:00 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**init_environment(void)
{
	char	**env;

	env = malloc(sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = NULL;
	env = env_getcwd(env);
	env = env_getpath(env);
	return (env);
}
