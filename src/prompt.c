/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:21:55 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 14:36:49 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	listen_prompt(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	if (!sh->prompt)
	{
		sh->error = 1;
		ft_putstr_fd("exit\n", 1);
		ft_free_values_exit(sh, sh->exit_status, 1);
	}
	if (sh->prompt[0] != '\0')
		add_history(sh->prompt);
}
