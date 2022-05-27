#include "minishell.h"

extern char	**environ;

static	char *choose_filename(void)
{
	char	*filename;
	int		file_exists;
	int		i;
	char	*nbr;

	i = 1;
	filename = ft_strdup("./heredoc");
	file_exists = open(filename, O_RDONLY);
	while (file_exists != -1)
	{
		close(file_exists);
		nbr = ft_itoa(i);
		filename = ft_strjoin_free(&filename, &nbr);
		file_exists = open(filename, O_RDONLY);
		i++;
	}
	close(file_exists);
	return (filename);
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

int	process_eof_heredoc(char **tmp, t_cmd_line ** cmd_line)
{
	ft_putstr_fd("bash: warning: here-document delimited by end-of-file\n", 1);
	ft_free_null_str(tmp);
	close((*cmd_line)->fdin);
	unlink((*cmd_line)->heredoc_name);
	ft_free_null_str(&(*cmd_line)->heredoc_name);
	return (1);
}

void	initialize_heredoc(t_cmd_line **cmd_line)
{
	(*cmd_line)->heredoc_name = choose_filename();
	(*cmd_line)->heredoc_mode = 1;
	(*cmd_line)->fdin = open((*cmd_line)->heredoc_name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
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

char	*trim_quotes_in_delimitor(char **value, int *i, int *j)
{
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	s1 = ft_strndup(&(*value)[*j], *i - *j);
	*i = *i + 1;
	*j = *i;
	while ((*value)[*i] && (*value)[*i] != SINGLE_QUOTE && (*value)[*i] != DOUBLE_QUOTE)
		*i = *i + 1;
	if ((*value)[*i] == SINGLE_QUOTE || (*value)[*i] == DOUBLE_QUOTE)
		s2 = ft_strndup(&(*value)[*j], *i - *j);
	*j = *i + 1;
	return (ft_strjoin_free(&s1, &s2));
}

char	*process_quotes_in_delimitor(char **value)
{
	char	*new;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = NULL;
	while ((*value)[i])
	{
		if ((*value)[i] == SINGLE_QUOTE || (*value)[i] == DOUBLE_QUOTE)
		{
			temp = trim_quotes_in_delimitor(value, &i, &j);
			new = ft_strjoin_free(&new, &temp);
		}
		i++;
	}
	temp = ft_strndup(&(*value)[j], i - j);
	return (ft_strjoin_free(&new, &temp));
}

//CTR+C => A voir si il faut vraiment le faire (ca a l'air tres relou)
//A RAJOUTER : GESTION DES QUOTES ET DES EXPANDS
	//heredoc_limit token must never be expanded
	//check if there are quotes in heredoc_limit token
	//if so,
		//set counter no expansion
		//remove quotes from heredoc_limit token
	//Else set specific rule in readline to expand env vars like regular env expansion
int	heredoc(char *delimitor, t_cmd_line ** cmd_line)
{
	char	*tmp;
	int		i;
	int		quotes;

	quotes = 0;
	if (str_has_quotes(delimitor))
	{
		delimitor = process_quotes_in_delimitor(&delimitor);
		quotes = 1;
	}
	initialize_heredoc(cmd_line);
	if ((*cmd_line)->fdin == -1)
		return (1);
	i = 0;
	while (1)
	{
		tmp = read_heredoc_line(cmd_line, quotes, delimitor);
		if (!tmp)
			return(1);
		if (!ft_strncmp(tmp, delimitor, ft_strlen(delimitor)) && ft_strlen(tmp) == ft_strlen(delimitor))
		{
			ft_free_null_str(&tmp);
			break;
		}
		if (i > 0)
			ft_putstr_fd("\n", (*cmd_line)->fdin);
		ft_putstr_fd(tmp, (*cmd_line)->fdin);
		ft_free_null_str(&tmp);
		i++;
	}
	return (0);
}
