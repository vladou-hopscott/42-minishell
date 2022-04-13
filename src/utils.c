/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:12:20 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/13 18:19:10 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

//integrer egalement les tabulations
int	str_has_only_spaces(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (!is_in_charset(str[i], CHARSET_SPACE_TABS))
			return (0);
		i++;
	}
	return (1);
}
