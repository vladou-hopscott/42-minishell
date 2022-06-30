/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:50 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/30 14:17:49 by vladimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt_values(t_sh *sh)
{
	sh->token_lst = NULL;
	sh->cmd_line_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
	sh->p_quote = NO_QUOTE;
	sh->error = 0;
	sh->has_pipe = 0;
}

void	init_program_values(t_sh *sh, char **env)
{
	ft_memset(sh, 0, sizeof(t_sh));
	init_prompt_values(sh);
	sh->exit_status = SUCCESS;
	sh->env = copy_environment(env);
	if (sh->error || sh->env == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		exit(FAILURE);
	}
}
