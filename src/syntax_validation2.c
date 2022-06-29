/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:19:46 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/29 19:38:00 by vnafissi         ###   ########.fr       */
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

int	error_first_is_pipe(int i)
{
	if (i == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	return (0);
}
