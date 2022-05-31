/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:36:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/31 21:37:35 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

char	*expand_envvar(char *str, int *i, int *j, char **s1, t_quote qs)
{
	char	*env_key;
	char	*env_val;

	if (ft_strlen(str) == 1
		|| !ft_strncmp(str, "$$", 2)
		|| (!ft_strncmp(str, "$\"", 2) && qs == DOUBLE_QUOTE)
		|| (!ft_strncmp(str, "$\'", 2) && qs == DOUBLE_QUOTE))
	{
		*s1 = ft_strjoin(*s1, "$");
		*i = *i + 1;
		*j = *i;
		return (*s1);
	}
	env_key = delimit_envvar(str);
	env_val = env_findkeyvalue(env_key, environ);
	if (ft_strlen(env_key) == 0)
		*i = *i + 1;
	*i = *i + ft_strlen(env_key);
	if (str[*i] != DOUBLE_QUOTE && str[*i] != SINGLE_QUOTE)
		*j = *i + 1;
	else
		*j = *i;
	if (env_val)
		*s1 = ft_strjoin_free(s1, &env_val);
	ft_free_null_str(&env_key);
	return (*s1);
}

//BASH VARIABLE NAME
// a-z, A-Z, _ and 0-9
// May NOT begin with a number
char	*delimit_envvar(char *str)
{
	int		i;
	char	*env_key;

	env_key = NULL;
	i = 1;
	if (ft_isdigit(str[i]))
		return (env_key);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	env_key = ft_strndup(str + 1, i - 1);
	return (env_key);
}

char	*expand_envvars_in_token(char **value)
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;
	int		quote_status;

	if (!str_has_dollar_without_quotes(*value))
		return (NULL);
	i = 0;
	j = 0;
	s1 = NULL;
	quote_status = NO_QUOTE;
	while ((*value)[i])
	{
		quote_status = check_quote_status_in_str((*value)[i], quote_status);
		if (quote_status == NO_QUOTE && (*value)[i] == '$')
		{
			s2 = ft_strndup(&(*value)[j], i - j);
			s1 = ft_strjoin_free(&s1, &s2);
			s1 = expand_envvar(&(*value)[i], &i, &j, &s1, quote_status);
		}
		i++;
	}
	s2 = ft_strndup(&(*value)[j], i - j);
	return (ft_strjoin_free(&s1, &s2));
}
