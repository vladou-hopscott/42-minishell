/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:23:39 by vladimir          #+#    #+#             */
/*   Updated: 2022/07/25 17:38:33 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_delete_heredoc_file(t_cmd_line *cmd_line, int del_hd_file)
{
	if (del_hd_file)
	{
		if (cmd_line->heredoc_mode == 1)
			unlink(cmd_line->heredoc_name);
	}
	ft_free_null_str(&cmd_line->heredoc_name);
}

void	free_cmd_line_lst(t_cmd_line *cmd_line, int del_hd_file)
{
	t_cmd_line	*next;

	while (cmd_line)
	{
		next = cmd_line->next;
		free_token_lst(cmd_line->token_lst);
		ft_free_null_str(&cmd_line->cmd);
		free_delete_heredoc_file(cmd_line, del_hd_file);
		if (cmd_line->args)
			ft_freetbl(cmd_line->args, -1);
		if (cmd_line->fdin != 0 && cmd_line->fdin != -1)
			close(cmd_line->fdin);
		if (cmd_line->fdout != 1 && cmd_line->fdout != -1)
			close(cmd_line->fdout);
		free(cmd_line);
		cmd_line = NULL;
		cmd_line = next;
	}
}

void	free_values(t_sh *sh, int free_env, int del_hd_file)
{
	free_token_lst(sh->token_lst);
	ft_free_null_str(&sh->prompt);
	free_cmd_line_lst(sh->cmd_line_lst, del_hd_file);
	if (free_env)
		ft_freetbl(sh->env, -1);
}

void	ft_free_values_exit(t_sh *sh, int exit_status, int del_hd_file)
{
	int	i;

	free_values(sh, 1, del_hd_file);
	rl_clear_history();
	i = 0;
	while (i < 1024)
	{
		if (!read(i, 0, 0))
			close(i);
		i++;
	}
	exit(exit_status);
}
