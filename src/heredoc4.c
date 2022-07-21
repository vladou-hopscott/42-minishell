/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:34:34 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/21 15:01:03 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

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

char	*delimit_envvar_heredoc(char *str)
{
	int		i;
	char	*env_key;

	env_key = NULL;
	i = 1;
	if (ft_isdigit(str[i]))
		return (NULL);
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	env_key = ft_strndup(str + 1, i - 1);
	return (env_key);
}

char	*manage_double_dolls(int *i, int *j, char **s1)
{
	char	*tmp;

	tmp = *s1;
	*s1 = ft_strjoin(*s1, "$");
	ft_free_null_str(&tmp);
	*i = *i + 1;
	*j = *i;
	return (*s1);
}

char	*expand_envvar_in_heredoc(char *str, int *i, int *j, char **s1)
{
	char	*env_key;
	char	*env_val;

	env_key = NULL;
	env_val = NULL;
	if (!ft_strncmp(str, "$$", 2))
	{
		*s1 = manage_double_dolls(i, j, s1);
		return (*s1);
	}
	env_key = delimit_envvar_heredoc(str);
	if (env_key && env_key[0] == '\0')
		env_val = ft_strdup("$");
	else
		env_val = env_findkeyvalue(env_key, g_sh.env);
	if (!env_key)
		*i = *i + 1;
	*i = *i + ft_strlen(env_key);
	*j = *i + 1;
	if (env_val)
		*s1 = ft_strjoin_free(s1, &env_val);
	ft_free_null_str(&env_key);
	return (*s1);
}
