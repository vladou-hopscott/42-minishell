/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:21:55 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/21 20:27:10 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//The line returned is allocated with malloc(3);
//the caller must free it when finished.
void	listen_prompt(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	if (!sh->prompt)
	{
		sh->error = 1;
		ft_putstr_fd("exit\n", 1);
		exit(sh->exit_status);
	}
	if (sh->prompt[0] != '\0')
		add_history(sh->prompt);
}
