/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:18:22 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/20 19:38:39 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_within_token(t_token **token)
{
	if (!str_has_space_without_quotes((*token)->value))
		return (*token);
	return (create_tokens_within_tokens(token, (*token)->value));
}

t_token	*create_tokens_within_tokens(t_token **token, char *str)
{
	int		i;
	int		j;
	int		quote_status;
	// char	*tmp;

	quote_status = NO_QUOTE;
	i = 0;
	j = 0;
	while (str[i])
	{
		quote_status = check_quote_status_in_str(str[i], quote_status);
		if (quote_status == NO_QUOTE && str[i] == ' ')
		{
			if (j == 0)
			{
				// tmp = (*token)->value;
				(*token)->value = ft_strndup(str, i);
				// ft_free_null_str(&tmp);
			}
			else
				*token = add_middle_token(
						(*token), STR, ft_strndup(&str[j], i - j));
			j = i + 1;
		}
		i++;
	}
	if (i > j)
		*token = add_middle_token((*token), STR, ft_strndup(&str[j], i - j));
	ft_free_null_str(&str);
	return (*token);
}

void	expand_envvars_in_tokens(t_cmd_line **cmd_line)
{
	t_token	*token;
	char	*new_value;
	char	*temp;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == STR)
		{
			new_value = expand_envvars_in_token(&token->value);
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
