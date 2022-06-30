/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:21:55 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/30 13:11:06 by swillis          ###   ########.fr       */
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
		exit(SUCCESS);
	}
	add_history(sh->prompt);
}
