#include "minishell.h"

extern char	**environ;

char	*trim_quotes_in_delimitor(char **value, int *i, int *j)
{
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	s1 = ft_strndup(&(*value)[*j], *i - *j);
	*i = *i + 1;
	*j = *i;
	while ((*value)[*i] && (*value)[*i] != SINGLE_QUOTE
			&& (*value)[*i] != DOUBLE_QUOTE)
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

void	process_delimitor(char **delimitor, int	*quotes)
{
	if (str_has_quotes(*delimitor))
	{
		*delimitor = process_quotes_in_delimitor(delimitor);
		*quotes = 1;
	}
}

int	is_delimitor(char **tmp, char **delimitor)
{
	if (!ft_strncmp(*tmp, *delimitor, ft_strlen(*delimitor))
		&& ft_strlen(*tmp) == ft_strlen(*delimitor))
	{
		ft_free_null_str(tmp);
		return (1);
	}
	return (0);
}

int	heredoc(char *delimitor, t_cmd_line **cmd_line)
{
	char	*tmp;
	int		i;
	int		quotes;

	quotes = 0;
	process_delimitor(&delimitor, &quotes);
	if (initialize_heredoc(cmd_line))
		return (1);
	i = 0;
	while (1)
	{
		tmp = read_heredoc_line(cmd_line, quotes, delimitor);
		if (!tmp)
			return (1);
		if (is_delimitor(&tmp, &delimitor))
			break ;
		if (i > 0)
			ft_putstr_fd("\n", (*cmd_line)->fdin);
		ft_putstr_fd(tmp, (*cmd_line)->fdin);
		ft_free_null_str(&tmp);
		i++;
	}
	return (0);
}
