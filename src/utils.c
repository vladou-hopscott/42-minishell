#include "minishell.h"
#include "parsing.h"

//integrer egalement les tabulations
int	str_has_only_spaces(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (!is_in_charset(str[i], CHARSET_SPACE_TABS))
			return (0);
		i++;
	}
	return (1);
}

int	str_has_quotes(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (is_in_charset(str[i], "\'\""))
			return (1);
		i++;
	}
	return (0);
}

int str_has_charset(char *str, char *charset)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (is_in_charset(str[i], charset))
			return (1);
		i++;
	}
	return (0);
}

int	str_has_space_without_quotes(char *str)
{
	int	i;
	int	quote_status;

	quote_status = NO_QUOTE;
	i = 0;
	while(str[i])
	{
		quote_status = check_quote_status_in_str(str[i], quote_status);
		if (quote_status == NO_QUOTE && str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	str_has_dollar_without_quotes(char *str)
{
	int	quote_status;
	int	i;

	i = 0;
	quote_status = NO_QUOTE;
	while (str[i])
	{
		quote_status = check_quote_status_in_str(str[i], quote_status);
		if (quote_status == NO_QUOTE && str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
