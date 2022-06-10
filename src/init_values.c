/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:50 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/31 20:55:53 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_values(t_sh *sh)
{
	sh->token_lst = NULL;
	sh->cmd_line_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
	sh->p_quote = NO_QUOTE;
	sh->error = 0;
}
void	init_program_values(t_sh *sh)
{
	sh->exit_status = 0;
}

void	free_token_lst(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		ft_free_null_str(&token->value);
		free(token);
		token = next;
	}
}

void	free_cmd_line_lst(t_cmd_line *cmd_line)
{
	t_cmd_line	*next;

	while (cmd_line)
	{
		next = cmd_line->next;
		free_token_lst(cmd_line->token_lst);
		ft_free_null_str(&cmd_line->cmd);
		ft_freetbl(cmd_line->args, -1);
		free(cmd_line);
		cmd_line = NULL;
		cmd_line = next;
	}
}

void	free_values(t_sh *sh, int free_env)
{
	free_token_lst(sh->token_lst);
	ft_free_null_str(&sh->prompt);
	free_cmd_line_lst(sh->cmd_line_lst);
	if (free_env)
		ft_freetbl(sh->env, -1);
}
