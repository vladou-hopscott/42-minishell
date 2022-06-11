/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:56:01 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/11 18:47:45 by vladimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_string_token(t_sh *sh, char *prompt)
{
	char	*tmp;
	char	*str;
	int		j;

	j = 0;
	while (prompt[j])
	{
		if (is_in_charset(prompt[j], CHARSET_SEP) && sh->p_quote == NO_QUOTE)
			break ;
		j++;
		sh->p_quote = check_quote_status_in_str(prompt[j], sh->p_quote);
	}
	tmp = ft_strndup(prompt, j);
	str = ft_strtrim(tmp, CHARSET_SPACE_TABS);
	free(tmp);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}

void	process_redirect_token(t_sh *sh)
{
	if (sh->prompt[sh->p_index] == RED_INPUT
		&& sh->prompt[sh->p_index + 1] == RED_INPUT)
	{
		sh->token_lst = add_back_token(sh->token_lst, HEREDOC, "<<");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == RED_OUTPUT
		&& sh->prompt[sh->p_index + 1] == RED_OUTPUT)
	{
		sh->token_lst = add_back_token(sh->token_lst, RED_APPEND, ">>");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == RED_INPUT)
		sh->token_lst = add_back_token(sh->token_lst, RED_INPUT, "<");
	else if (sh->prompt[sh->p_index] == RED_OUTPUT)
		sh->token_lst = add_back_token(sh->token_lst, RED_OUTPUT, ">");
}

void	tokenizer(t_sh *sh)
{
	char	*str;

	str = NULL;
	sh->p_quote = check_quote_status_in_str(
			sh->prompt[sh->p_index], sh->p_quote);
	if (sh->p_quote == NO_QUOTE && is_in_charset(
			sh->prompt[sh->p_index], CHARSET_SEP))
	{
		if (sh->prompt[sh->p_index] == PIPE)
			sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
		else
			process_redirect_token(sh);
	}
	else
	{
		str = process_string_token(sh, &sh->prompt[sh->p_index]);
		if (!str_has_only_spaces(str))
			sh->token_lst = add_back_token(sh->token_lst, STR, str);
		ft_free_null_str(&str);
	}
}

void	lexer(t_sh *sh)
{
	if (sh->error)
		return ;
	if (check_for_quotes(sh))
		return ;
	while (sh->prompt[sh->p_index])
	{
		tokenizer(sh);
		sh->p_index ++;
	}
	if (!sh->token_lst)
	{
		sh->error = 1;
		return ;
	}
	check_syntax_errors(sh);
}
