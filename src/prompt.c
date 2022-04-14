/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:56:50 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/14 13:58:04 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void listen_prompt(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");

	//il faut stocker la commande entrée dans le prompt dans l'historique, voir la fonction

	// env debugging
	int i = 0;
	while (g_env && g_env[i])
	{
		printf("env[%d] -> %s\n", i, g_env[i]);
		i++;
	}
}
