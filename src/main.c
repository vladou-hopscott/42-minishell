/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:43:34 by swillis           #+#    #+#             */
/*   Updated: 2022/04/13 16:43:06 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void initialization(t_sh *sh)
{
	init_values(sh);
	while (1)
	{
		listen_prompt(sh); //générer un prompt avec readline() et enregistrer la commande tapée
		lexer(sh); //analyse lexicale de la commande
		init_values(sh);
	}
}

int	main(int ac, char **av)
{
	//Faut-il déclarer sh comme une variable globale (pour garder en mémoire les commandes successives ?)
	t_sh	sh;

	(void)ac;
	(void)av;

	initialization(&sh);

	//penser à free tout ce qui a été initialisé avec readline
	return (0);
}
