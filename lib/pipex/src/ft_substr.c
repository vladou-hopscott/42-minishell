/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:46:02 by swillis           #+#    #+#             */
/*   Updated: 2022/04/11 22:02:35 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (0);
	if (ft_strlen(s) > len + start)
		str = malloc((len + 1) * sizeof(char));
	else if (ft_strlen(s) > start)
		str = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	else
		str = malloc(sizeof(char));
	if (!str)
		return (0);
	i = 0;
	j = start;
	if (start < ft_strlen(s))
	{
		while (s[i] && (i < len) && (j < ft_strlen(s)))
			str[i++] = s[j++];
	}
	str[i] = '\0';
	return (str);
}
