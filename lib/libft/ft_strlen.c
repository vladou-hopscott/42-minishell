/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:10:06 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/11 18:10:25 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// calcule la longueur de la chaîne de caractères s,
// sans compter l'octet nul « \0 » final.
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

