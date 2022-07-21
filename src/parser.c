/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:56:16 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/21 20:41:38 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tokens_in_cmd_lines(t_sh *sh)
{
	t_token		*token;
	t_cmd_line	*start;

	token = sh->token_lst;
	sh->cmd_line_lst = add_back_cmd_line(sh->cmd_line_lst);
	start = sh->cmd_line_lst;
	while (token && sh->cmd_line_lst)
	{
		if (token->type != PIPE)
			sh->cmd_line_lst->token_lst = add_back_token(
					sh->cmd_line_lst->token_lst, token->type, token->value);
		else
		{
			sh->cmd_line_lst = add_back_cmd_line(sh->cmd_line_lst);
			sh->cmd_line_lst = sh->cmd_line_lst->next;
		}
		token = token->next;
	}
	sh->cmd_line_lst = start;
}

void	process_quotes_in_cmd_lines(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		process_quotes_in_tokens(&sh->cmd_line_lst);
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

void	expand_envvars_without_quotes(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		expand_envvars_in_tokens(&sh->cmd_line_lst);
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

void	tokenize_after_env_exp(t_sh *sh)
{
	t_cmd_line	*start;
	t_token		*token;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		token = sh->cmd_line_lst->token_lst;
		while (token)
		{
			if (token->type == STR)
				token = tokenize_within_token(&token);
			token = token->next;
		}
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

void	parser(t_sh *sh)
{
	if (sh->error)
		return ;
	parse_tokens_in_cmd_lines(sh);
	update_token_type_heredoc_limit(sh);
	expand_envvars_without_quotes(sh);
	tokenize_after_env_exp(sh);
	process_quotes_in_cmd_lines(sh);
	update_token_type_str(sh);
	update_elems_cmd_lines(sh);
	if (!sh->cmd_line_lst)
		sh->error = 1;
}
