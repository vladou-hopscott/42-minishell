#include "minishell.h"

int	ft_tbllen(char **tbl)
{
	int	i;

	i = 0;
	while (tbl && tbl[i])
		i++;
	i += 1;
	return (i);
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

void	tbl_append(char **tbl, char *str)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * (ft_tbllen(tbl) + 1));
	if (!new)
		return ;
	i = 0;
	while (tbl && tbl[i])
	{
		new[i] = ft_strdup(tbl[i]);
		i++;
	}
	new[i++] = str;
	new[i] = NULL;
	// ft_freetbl(tbl, -1);
	tbl = new;
}

void	env_export(char *key, char *value, char **env)
{
	int		i;
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(key, "=");
	str = ft_strjoin(tmp, value);
	free(tmp);
	i = env_findkeypos(key, env);
	if (i >= 0)
	{
		free(env[i]);
		env[i] = str;
	}
	else
		tbl_append(env, str);
}

void	env_getcwd(char **env)
{
	char	*buf;
	char	*cwd;

	buf = getcwd(NULL, 0);
	cwd = ft_strdup(buf);
	free(buf);
	env_export("CWD", cwd, env);
	free(cwd);
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

void	env_getpath(char **env)
{
	char	*path;
	char	*cwd;

	cwd = env_findkeyvalue("CWD", env);
	path = ft_strjoin(cwd, "/bin");
	free(cwd);
	env_export("PATH", path, env);
	free(path);
}

char	**init_environment(void)
{
	char	**env;

	env = malloc(sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = NULL;
	env_getcwd(env);
	env_getpath(env);
	return (env);
}
