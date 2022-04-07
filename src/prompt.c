/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:56:50 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/07 18:41:19 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void listen_prompt(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	printf("sh->prompt: %s\n", sh->prompt);

	//il faut stocker la commande entrée dans le prompt dans l'historique, voir la fonction
}
