/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:03 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 17:03:23 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_fdout(t_token *token, t_cmd_line **cmd_line)
{
	if (token->type == OUTPUT)
	{
		(*cmd_line)->fdout = open(token->value,
				O_WRONLY | O_CREAT | O_TRUNC, 00644);
		(*cmd_line)->append_mode = 0;
	}
	else
	{
		(*cmd_line)->fdout = open(token->value,
				O_WRONLY | O_CREAT | O_APPEND, 00644);
		(*cmd_line)->append_mode = 1;
	}
	if (open_file_check((*cmd_line)->fdout, token->value))
		return (1);
	return (0);
}

int	open_file_fdin(char *filename, t_cmd_line **cmd_line)
{
	(*cmd_line)->fdin = open(filename, O_RDONLY);
	if (open_file_check((*cmd_line)->fdin, filename))
		return (1);
	return (0);
}

void	close_file_fdin(t_cmd_line **cmd_line)
{
	if ((*cmd_line)->fdin != 0)
		close((*cmd_line)->fdin);
	if ((*cmd_line)->heredoc_mode == 1)
	{
		(*cmd_line)->heredoc_mode = 0;
		unlink((*cmd_line)->heredoc_name);
	}
}

int	update_fdout(t_cmd_line **cmd_line, t_token *token)
{
	if ((*cmd_line)->fdout != 1)
		close((*cmd_line)->fdout);
	if (open_file_fdout(token, cmd_line))
		return (1);
	return (0);
}

int	update_fdin(t_cmd_line **cmd_line, t_token *token)
{
	int		error;

	error = 0;
	close_file_fdin(cmd_line);
	if (token->type == INPUT)
		error = open_file_fdin(token->value, cmd_line);
	else
		error = heredoc(token->value, cmd_line);
	if (error)
		return (1);
	return (0);
}
