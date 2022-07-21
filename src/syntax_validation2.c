/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:19:46 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/21 12:24:01 by swillis          ###   ########.fr       */
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
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	return (0);
}

int	error_first_is_pipe(int i)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	return (0);
}
