/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:04:43 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/31 21:18:13 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	update_token_type(t_token **token, int *has_cmd)
{
	if ((*token)->type == RED_INPUT)
		(*token)->next->type = INPUT;
	else if ((*token)->type == RED_OUTPUT)
		(*token)->next->type = OUTPUT;
	else if ((*token)->type == RED_APPEND)
		(*token)->next->type = OUTPUT_APPEND;
	else if ((*token)->type == HEREDOC)
		(*token)->next->type = HEREDOC_LIMIT;
	else if ((*token)->type == STR)
	{
		if (!(*has_cmd))
		{
			(*token)->type = CMD;
			*has_cmd = 1;
		}
		else
			(*token)->type = ARG;
	}
}

void	update_tokens(t_cmd_line **cmd_line)
{
	t_token		*token;
	int			has_cmd;

	token = (*cmd_line)->token_lst;
	has_cmd = 0;
	while (token)
	{
		update_token_type(&token, &has_cmd);
		token = token->next;
	}
}

void	update_token_type_str(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		update_tokens(&sh->cmd_line_lst);
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

void	update_tokens_hd_limit(t_cmd_line **cmd_line)
{
	t_token		*token;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == HEREDOC)
			token->next->type = HEREDOC_LIMIT;
		token = token->next;
	}
}

void	update_token_type_heredoc_limit(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		update_tokens_hd_limit(&sh->cmd_line_lst);
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}
