/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:41:45 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/11 18:21:55 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "../libft/libft.h"

int	isin_charset(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char *string_token(t_sh *sh, char *prompt)
{
	char *str;
	int j = 0;

	while (prompt[j])
	{
		if (isin_charset(prompt[j]))
			break;
		j++;
	}
	str = ft_strdup(prompt, j);
	if (j == 0)
		printf("ERROR TO CHECK\n");
	sh->p_index += j - 1;
	return (str);
}

int	isonly_space(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	tokenizer(t_sh *sh, char first, char second)
{
	(void)sh;
	char	*str;

	str = NULL;
	// ajoute le bon token à la liste chainée des tokens sh->token_lst
	if (first == PIPE)
		sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
	else if (first == RED_LEFT || first == RED_RIGHT)
	{
		//printf("first=%c, second=%c\n", first, second);
		if (first == RED_LEFT && second == RED_LEFT)
			sh->token_lst = add_back_token(sh->token_lst, DOUBLE_RED_LEFT, "<<");
		else if (first == RED_RIGHT && second == RED_RIGHT)
			sh->token_lst = add_back_token(sh->token_lst, DOUBLE_RED_RIGHT, ">>");
		else if (first == RED_LEFT)
			sh->token_lst = add_back_token(sh->token_lst, RED_LEFT, "<");
		else if (first == RED_RIGHT)
			sh->token_lst = add_back_token(sh->token_lst, RED_RIGHT, ">");
	}
	else
	{
		str = string_token(sh, &sh->prompt[sh->p_index]);
		if (!isonly_space(str))
			sh->token_lst = add_back_token(sh->token_lst, STR, str);
	}
}

void lexer(t_sh *sh)
{
	int sec;

	while (sh->prompt[sh->p_index])
	{
		//à faire à un moment : gérer les tabulations et les espaces (les virer)
		printf("i=%d\n", sh->p_index);
		sec = 0;
		if ((sh->prompt[sh->p_index] == RED_LEFT || sh->prompt[sh->p_index] == RED_RIGHT) && sh->prompt[sh->p_index + 1]) //sert à vérifier si il y a 2 '<' ou 2 '>' qui s'enchainent
		{
			if (sh->prompt[sh->p_index + 1] == RED_LEFT)
			{
				sec = RED_LEFT;
				sh->p_index++;
			}
			else if (sh->prompt[sh->p_index + 1] == RED_RIGHT)
			{
				sec = RED_RIGHT;
				sh->p_index++;
			}

		}
		tokenizer(sh, sh->prompt[sh->p_index], sec);
		sh->p_index++;
	}
	print_tokens(sh->token_lst);
	printf("list length=%d\n", list_length(sh->token_lst));
}

