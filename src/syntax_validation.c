/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:33 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/31 21:28:25 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(t_token_type type)
{
	if (type == RED_INPUT
		|| type == RED_OUTPUT
		|| type == HEREDOC
		|| type == RED_APPEND)
		return (1);
	return (0);
}

int	error_next_is_pipe(t_token *token)
{
	if (token->type == PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	return (0);
}

int	error_next_is_null(t_token *token)
{
	if (token == NULL)
	{
		ft_putstr_fd("bash: syntax error near unexpected token 'newline'\n", 2);
		return (1);
	}
	return (0);
}

int	error_next_is_redirection(t_token *token)
{
	char	*err;

	err = NULL;
	if (token->type == RED_INPUT)
		err = "<";
	else if (token->type == RED_OUTPUT)
		err = ">";
	else if (token->type == HEREDOC)
		err = "<<";
	else if (token->type == RED_APPEND)
		err = ">>";
	if (err)
	{
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

void	check_syntax_errors(t_sh *sh)
{
	t_token	*token;

	token = sh->token_lst;
	while (token)
	{
		if (is_redirection(token->type))
		{
			if (error_next_is_null(token->next))
				sh->error = 1;
			else if (error_next_is_pipe(token->next))
				sh->error = 1;
			else if (error_next_is_redirection(token->next))
				sh->error = 1;
		}
		else if (token->type == PIPE)
		{
			if (error_next_is_null(token->next))
				sh->error = 1;
			else if (error_next_is_pipe(token->next))
				sh->error = 1;
		}
		token = token->next;
		if (sh->error == 1)
			return ;
	}
}
