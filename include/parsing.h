/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:12:59 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/08 18:06:09 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//enum sert à créer un index de 0 à N (ou bien à partir de la valeur ascii du caractère). https://linux.die.net/man/3/enum
//Ici on l'utilise pour chaque type de token : classement en redirections, args (tout le reste, les "littéraux")
typedef enum token_type
{
	PIPE = '|',
	RED_LEFT = '<',
	RED_RIGHT = '>',
	ARG,
} t_token_type;

// liste chaînée. Chaque token représente un caractère tokenisé, chaîné au token précédent / suivant
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
} t_token;

#endif
