/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:36:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/11 17:05:46 by vladimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

int	check_lonely_dollar(char *str, t_quote qs)
{
	if (ft_strlen(str) == 1
		|| !ft_strncmp(str, "$$", 2)
		|| (!ft_strncmp(str, "$\"", 2) && qs == DOUBLE_QUOTE)
		|| (!ft_strncmp(str, "$\'", 2) && qs == SINGLE_QUOTE))
		return (1);
	return (0);
}

char	*expand_envvar(char *str, t_idx *idx, char **s1, t_quote qs)
{
	char	*env_key;
	char	*env_val;
	int		k;

	k = 0;
	if (check_lonely_dollar(str, qs))
	{
		*s1 = ft_strjoin(*s1, "$");
		idx->i++;
		idx->j = idx->i;
		return (*s1);
	}
	env_key = delimit_envvar(str);
	printf("env_key=%s\n", env_key);
	// if (ft_strncmp(env_key, "?", 1))
		// env_val = 	
	env_val = env_findkeyvalue(env_key, environ);
	printf("env_val=%s\n", env_val);
	if (ft_strlen(env_key) == 0)
		k++;
	k += ft_strlen(env_key);
	idx->i += k;
	if (str[k] != DOUBLE_QUOTE && str[k] != SINGLE_QUOTE)
		idx->j = idx->i + 1;
	else
		idx->j = idx->i;
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
	if (str[i] == '?')
		return ("?");
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	env_key = ft_strndup(str + 1, i - 1);
	return (env_key);
}

char	*expand_envvars_in_token(char **value)
{
	char	*s1;
	char	*s2;
	int		quote_status;
	t_idx	idx;

	if (!str_has_dollar_without_quotes(*value))
		return (NULL);
	idx.i = 0;
	idx.j = 0;
	s1 = NULL;
	quote_status = NO_QUOTE;
	while ((*value)[idx.i])
	{
		quote_status = check_quote_status_in_str((*value)[idx.i], quote_status);
		if (quote_status == NO_QUOTE && (*value)[idx.i] == '$')
		{
			s2 = ft_strndup(&(*value)[idx.j], idx.i - idx.j);
			s1 = ft_strjoin_free(&s1, &s2);
			s1 = expand_envvar(&(*value)[idx.i], &idx, &s1, quote_status);
			if ((*value)[idx.i] == DOUBLE_QUOTE || (*value)[idx.i] == SINGLE_QUOTE)
				quote_status = check_quote_status_in_str((*value)[idx.i], quote_status);
		}
		idx.i++;
	}
	s2 = ft_strndup(&(*value)[idx.j], idx.i - idx.j);
	return (ft_strjoin_free(&s1, &s2));
}
