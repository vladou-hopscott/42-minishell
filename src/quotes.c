/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:22:41 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/31 21:25:11 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			s2 = ft_strndup(&(*value)[*j], *i - *j);
			s1 = ft_strjoin_free(&s1, &s2);
			s1 = expand_envvar(&(*value)[*i], i, j, &s1, DOUBLE_QUOTE);
		}
		if ((*value)[*i] == DOUBLE_QUOTE)
			continue ;
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

	if (!str_has_quotes(*value))
		return (NULL);
	i = 0;
	j = 0;
	new = NULL;
	while ((*value)[i])
	{
		if ((*value)[i] == SINGLE_QUOTE || (*value)[i] == DOUBLE_QUOTE)
		{
			if ((*value)[i] == SINGLE_QUOTE)
				temp = trim_single_quotes_in_token(value, &i, &j);
			else
				temp = trim_double_quotes_in_token(value, &i, &j);
			new = ft_strjoin_free(&new, &temp);
		}
		i++;
	}
	temp = ft_strndup(&(*value)[j], i - j);
	return (ft_strjoin_free(&new, &temp));
}

void	process_quotes_in_tokens(t_cmd_line **cmd_line)
{
	t_token	*token;
	char	*new_value;
	char	*temp;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == STR)
		{
			new_value = process_quotes_in_token(&token->value);
			if (new_value)
			{
				temp = token->value;
				token->value = new_value;
				ft_free_null_str(&temp);
			}
		}
		token = token->next;
	}
}
