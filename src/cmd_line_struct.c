/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:12 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 17:02:54 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_cmd(t_cmd_line **cmd_line)
{
	t_token	*token;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == CMD)
		{
			(*cmd_line)->cmd = ft_strdup(token->value);
			if (!(*cmd_line)->cmd)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	update_args(t_cmd_line **cmd_line)
{
	t_token	*token;
	int		i;

	token = (*cmd_line)->token_lst;
	(*cmd_line)->args = ft_calloc(count_arg_tokens(token) + 1, sizeof(char *));
	if (!(*cmd_line)->args)
		return (1);
	i = 0;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
		{
			(*cmd_line)->args[i] = ft_strndup(
					token->value, ft_strlen(token->value));
			if (!(*cmd_line)->args[i])
				return (1);
			i++;
		}
		token = token->next;
	}
	(*cmd_line)->args[i] = NULL;
	return (0);
}

int	update_fdin_fdout(t_cmd_line **cmd_line)
{
	t_token	*token;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == INPUT || token->type == HEREDOC_LIMIT)
		{
			if (update_fdin(cmd_line, token))
				return (1);
		}
		else if (token->type == OUTPUT || token->type == OUTPUT_APPEND)
		{
			if (update_fdout(cmd_line, token))
				return (1);
		}
		token = token->next;
	}
	return (0);
}

void	update_elems_cmd_lines(t_sh *sh)
{
	t_cmd_line	*cmdl;

	cmdl = sh->cmd_line_lst;
	while (cmdl)
	{
		if (update_cmd(&cmdl)
			|| update_args(&cmdl)
			|| update_fdin_fdout(&cmdl))
		{
			sh->error = 1;
			if (!sh->exit_status)
				sh->exit_status = FAILURE;
		}
		cmdl = cmdl->next;
	}
}
