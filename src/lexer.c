/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:41:45 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/08 18:28:09 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"


void	tokenizer(t_sh *sh, char first, char second)
{
	(void)second;
	(void)sh;

	// ajoute le bon token à la liste chainée des tokens sh->token_lst
	if (first == PIPE)
	{
		add_back_token(sh->token_lst, PIPE, "|");
		printf("added PIPE to token linked list\n");
	}
	else if (first == RED_LEFT || first == RED_LEFT)
		printf("REDIRECTION < OU >\n");
	else
		printf("LITTERAL\n");
}

void lexer(t_sh *sh)
{
	int	i;
	int sec;

	i = 0;
	while (sh->prompt[i])
	{
		//à faire : gérer les tabulations et les espaces (les virer)

		sec = 0;
		if (sh->prompt[i + 1]) //sert à vérifier si il y a 2 '<' ou 2 '>' qui s'enchainent
		{
			if (sh->prompt[i + 1] == RED_LEFT)
				sec = RED_LEFT;
			else if (sh->prompt[i + 1] == RED_RIGHT)
				sec = RED_RIGHT;
		}
		tokenizer(sh, sh->prompt[i], sec);
		i++;
	}
}
