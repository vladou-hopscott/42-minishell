/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:05:39 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/13 11:06:40 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	init_values(t_sh *sh)
{
	sh->token_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
}
