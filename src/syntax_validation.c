/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 19:37:25 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/21 12:24:01 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_next_is_null(t_token *token)
{
	if (token == NULL)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
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
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

int	has_redirection_errors(t_token *token)
{
	if (error_next_is_null(token->next)
		|| error_next_is_pipe(token->next)
		|| error_next_is_redirection(token->next))
		return (1);
	return (0);
}

void	check_syntax_errors(t_sh *sh)
{
	t_token	*token;
	int		i;

	i = 0;
	token = sh->token_lst;
	while (token)
	{
		if (is_redirection(token->type) && has_redirection_errors(token))
				sh->error = 1;
		else if (token->type == PIPE)
		{
			if (error_next_is_null(token->next)
				|| error_next_is_pipe(token->next)
				|| error_first_is_pipe(i))
					sh->error = 1;
		}
		token = token->next;
		i++;
		if (sh->error == 1)
		{
			sh->exit_status = MAJOR_FAILURE;
			return ;
		}
	}
}
