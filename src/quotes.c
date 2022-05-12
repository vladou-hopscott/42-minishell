#include "minishell.h"

extern char	**environ;

int	check_quote_status_in_str(char c, int quote_status)
{
	if (quote_status == NO_QUOTE)
	{
		if (c == SINGLE_QUOTE)
			quote_status = SINGLE_QUOTE;
		else if (c == DOUBLE_QUOTE)
			quote_status = DOUBLE_QUOTE;
	}
	else if (quote_status == SINGLE_QUOTE)
	{
		if (c == SINGLE_QUOTE)
			quote_status = NO_QUOTE;
	}
	else if (quote_status == DOUBLE_QUOTE)
	{
		if (c == DOUBLE_QUOTE)
			quote_status = NO_QUOTE;
	}
	return quote_status;
}

//check if there are unclosed quotes. if so, return error status 1
int check_for_quotes(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->prompt && sh->prompt[i])
	{
		sh->p_quote = check_quote_status_in_str(sh->prompt[i], sh->p_quote);
		i++;
	}
	if (sh->p_quote != NO_QUOTE)
	{
		sh->error = 1;
		ft_putstr_fd("bash : unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}

char	*trim_double_quotes_in_token(char **value, int *i, int *j)
{
	char	*s1;
	char	*s2;

	s1 = ft_strndup(&(*value)[*j], *i - *j);
	*i = *i + 1;
	*j = *i;
	while ((*value)[*i] && (*value)[*i] != DOUBLE_QUOTE)
	{
		if ((*value)[*i] == '$')
		{
			s2 = ft_strndup(&(*value)[*j], *i - *j); //on enregistre ce qu'il y a entre le double quote et le $
			s1 = ft_strjoin_free(&s1, &s2); //on join ca a s1
			s1 = expand_envvar(&(*value)[*i], i, j, &s1);
		}
		*i = *i + 1;
	}
	if ((*value)[*i] == DOUBLE_QUOTE)
		s2 = ft_strndup(&(*value)[*j], *i - *j);
	*j = *i + 1;
	return (ft_strjoin_free(&s1, &s2));
}

char	*trim_single_quotes_in_token(char **value, int *i, int *j)
{
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	s1 = ft_strndup(&(*value)[*j], *i - *j);
	*i = *i + 1;
	*j = *i;
	while ((*value)[*i] && (*value)[*i] != SINGLE_QUOTE)
		*i = *i + 1;
	if ((*value)[*i] == SINGLE_QUOTE)
		s2 = ft_strndup(&(*value)[*j], *i - *j);
	*j = *i + 1;
	return (ft_strjoin_free(&s1, &s2));
}

char	*process_quotes_in_token(char **value)
{
	char	*new;
	char	*temp;
	int		i;
	int		j;

	if (!str_has_quotes(*value)) //if no quotes in token, skip
		return (NULL);
	i = 0;
	j = 0;
	new = NULL;
	while ((*value)[i])
	{
		if ((*value)[i] == SINGLE_QUOTE || (*value)[i] == DOUBLE_QUOTE) //on entre dans des single ou double quotes externes -> on doit les virer
		{
			if ((*value)[i] == SINGLE_QUOTE)
				temp = trim_single_quotes_in_token(value, &i, &j);
			else
				temp = trim_double_quotes_in_token(value, &i, &j);
			new = ft_strjoin_free(&new, &temp);
		}
		i++;
	}
	temp = ft_strndup(&(*value)[j], i - j); 	//join last part of string to new
	return (ft_strjoin_free(&new, &temp));
}
