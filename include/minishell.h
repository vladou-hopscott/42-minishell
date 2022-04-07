/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:47:18 by swillis           #+#    #+#             */
/*   Updated: 2022/04/07 16:58:51 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

//sert à créer un index de 0 à N (ou bien à partir de la valeur ascii du caractère) pour chaque type de token : https://linux.die.net/man/3/enum
typedef enum e_token
{
	PIP = '|',
	R_LEFT = '<',
	R_RIGHT = '>',
	DR_LEFT,
	DR_RIGHT,
	ARGS,
	ERROR,
	NUL,
	NONE
} t_token;


typedef struct s_lexer
{
	t_token			token;
	struct s_lexer	*prev;
	struct s_lexer	*next;
} t_lexer;

typedef struct s_minishell
{
	t_lexer			*lexer;
	char			*prompt;
}				t_minishell;

#endif
