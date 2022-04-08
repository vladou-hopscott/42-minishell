/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:47:18 by swillis           #+#    #+#             */
/*   Updated: 2022/04/08 18:25:14 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "parsing.h"

//********************** STRUCTURES **********************//

//structure principale du programme
typedef struct s_sh
{
	t_token			*token_lst;
	char			*prompt;
} t_sh;

//********************** FUNCTIONS **********************//

//**** PROMPT ****//
void	listen_prompt(t_sh *sh);

//**** LEXER ****//
void	lexer(t_sh *sh);
void	tokenizer(t_sh *sh, char first, char second);

t_token	*create_token(t_token_type type, char *value);
void	add_back_token(t_token *list, t_token_type type, char *value);




#endif

