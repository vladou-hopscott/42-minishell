/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:55:58 by swillis           #+#    #+#             */
/*   Updated: 2022/04/11 22:02:34 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(find) == 0)
		return ((char *)str);
	while ((str[i] != 0) && (i < len))
	{
		j = 0;
		while ((str[i + j] == find[j]) && (i + j < len))
		{
			if (j == ft_strlen(find) - 1)
			{
				return ((char *)&str[i]);
			}
			j++;
		}
		i++;
	}
	return (0);
}
