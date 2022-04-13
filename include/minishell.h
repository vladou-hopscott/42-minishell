/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:47:18 by swillis           #+#    #+#             */
/*   Updated: 2022/04/13 17:44:07 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "parsing.h"
# include "../libft/libft.h"

//********************** STRUCTURES **********************//

//structure principale du programme
typedef struct s_sh
{
	t_token			*token_lst;
	char			*prompt;
	int				p_index;
} t_sh;

//********************** FUNCTIONS **********************//

//********** INITIALIZATION **********//
void	init_values(t_sh *sh);

//********** PROMPT **********//
void	listen_prompt(t_sh *sh);

//********** LEXER **********//
void	lexer(t_sh *sh);
void	tokenizer(t_sh *sh);
char	*string_token(t_sh *sh, char *prompt);

//********** LINKED LIST TOKENS **********//
t_token	*create_token(t_token_type type, char *value);
t_token	*add_back_token(t_token *list, t_token_type type, char *value);
void	print_tokens(t_token *li);
int		list_length(t_token *li);
void	ft_set_null_free_list(t_token **a_list);

//********** UTILS **********//
int	str_has_only_spaces(char *str);

#endif

