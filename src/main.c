/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:43:34 by swillis           #+#    #+#             */
/*   Updated: 2022/04/07 17:10:36 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_prompt(t_minishell *game)
{
	game->prompt = readline("➜ ");
	printf("game->prompt: %s\n", game->prompt);
}


void initialization(t_minishell *game)
{
	while (1)
	{
		print_prompt(game);
	}
}

int	main(int ac, char **av)
{

	t_minishell	game;

	(void)ac;
	(void)av;

	initialization(&game);

	//penser à free tout ce qui a été initialisé avec readline
	return (0);
}
