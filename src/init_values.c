/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:05:39 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/15 17:21:46 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_values(t_sh *sh)
{
	sh->token_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
	sh->env = init_environment();
}

void	free_token_lst(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

void	free_values(t_sh *sh)
{
	free_token_lst(sh->token_lst);
	free(sh->prompt);
	ft_freetbl(sh->env, -1);
}