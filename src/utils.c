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
