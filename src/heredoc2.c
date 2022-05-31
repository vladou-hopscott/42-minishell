#include "minishell.h"

extern char	**environ;

int	process_eof_heredoc(char **tmp, t_cmd_line **cmd_line)
{
	ft_putstr_fd("bash: warning: here-document delimited by end-of-file\n", 1);
	ft_free_null_str(tmp);
	close((*cmd_line)->fdin);
	unlink((*cmd_line)->heredoc_name);
	ft_free_null_str(&(*cmd_line)->heredoc_name);
	return (1);
}

char	*expand_envvar_in_heredoc(char *str, int *i, int *j, char **s1)
{
	char	*env_key;
	char	*env_val;

	env_key = NULL;
	env_val = NULL;
	if (!ft_strncmp(str, "$$", 2))
	{
		*s1 = ft_strjoin(*s1, "$");
		*i = *i + 1;
		*j = *i;
		return (*s1);
	}
	env_key = delimit_envvar(str);
	if (env_key && env_key[0] == '\0')
		env_val = ft_strdup("$");
	else
		env_val = env_findkeyvalue(env_key, environ);
	if (!env_key)
		*i = *i + 1;
	*i = *i + ft_strlen(env_key);
	*j = *i + 1;
	if (env_val)
		*s1 = ft_strjoin_free(s1, &env_val);
	ft_free_null_str(&env_key);
	return (*s1);
}

char	*expand_envvars_in_heredoc(char **value)
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s1 = NULL;
	while ((*value)[i])
	{
		if ((*value)[i] == '$')
		{
			s2 = ft_strndup(&(*value)[j], i - j);
			s1 = ft_strjoin_free(&s1, &s2);
			s1 = expand_envvar_in_heredoc(&(*value)[i], &i, &j, &s1);
		}
		i++;
	}
	s2 = ft_strndup(&(*value)[j], i - j);
	return (ft_strjoin_free(&s1, &s2));
}

char	*expand_heredoc_line(char **str)
{
	char	*tmp;

	tmp = expand_envvars_in_heredoc(str);
	ft_free_null_str(str);
	return (tmp);
}

char	*read_heredoc_line(t_cmd_line **cmd_line, int quotes, char *delimitor)
{
	char	*str;

	str = readline("> ");
	if (!str)
	{
		process_eof_heredoc(&str, cmd_line);
		return (NULL);
	}
	if (!quotes)
	{
		if (!ft_strncmp(str, delimitor, ft_strlen(delimitor)) && ft_strlen(str) == ft_strlen(delimitor))
			return (str);
		else if (str_has_charset(str, "$"))
			str = expand_heredoc_line(&str);
	}
	return (str);
}
