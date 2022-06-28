/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:42:22 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/28 00:29:04 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define CHARSET_SEP "<>| "
# define CHARSET_SPACE_TABS " \n\v\t\f\r"

typedef enum token_type
{
	PIPE = '|',
	RED_INPUT = '<',
	RED_OUTPUT = '>',
	HEREDOC,
	RED_APPEND,
	OUTPUT,
	INPUT,
	OUTPUT_APPEND,
	HEREDOC_LIMIT,
	STR,
	ARG,
	CMD,
	BUILTIN,
}	t_token_type;

typedef enum quote
{
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	NO_QUOTE
}	t_quote;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quote;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_idx
{
	int				i;
	int				j;
}	t_idx;

typedef struct s_cmd_line
{
	char				*cmd;
	t_token				*token_lst;
	char				*str;
	char				**args;
	int					fdin;
	int					heredoc_mode;
	char				*heredoc_name;
	int					fdout;
	int					append_mode;
	int					pid;
	struct s_cmd_line	*next;
}	t_cmd_line;

#endif
