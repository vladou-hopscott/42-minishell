/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:56:50 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/13 16:35:47 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void listen_prompt(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	add_history(sh->prompt); //verifier si il y a d'autres choses a ajouter pour securiser ou stocker l'historique
}
