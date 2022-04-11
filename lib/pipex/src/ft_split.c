/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:36:18 by swillis           #+#    #+#             */
/*   Updated: 2022/04/11 22:02:31 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_freetbl(char **tbl, int pos)
{
	if (pos == -1)
	{
		pos = 0;
		while (tbl && tbl[pos])
			pos++;
	}
	while (pos >= 0)
	{
		if (tbl[pos])
			free(tbl[pos]);
		pos--;
	}
	free(tbl);
	return (0);
}

int	ft_wordcount(char *str, char c)
{
	int	i;
	int	wrd;

	i = 0;
	wrd = 0;
	while (str && str[i])
	{
		while ((c == str[i]) && str[i])
			i++;
		if ((c != str[i]) && str[i])
			wrd++;
		while ((c != str[i]) && str[i])
			i++;
	}
	return (wrd);
}

int	ft_wordlen(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && (c == str[i]))
		i++;
	while (str[i] && (c != str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

char	*ft_fillelem(char *s, char c, int i, char *elm)
{
	int	j;

	j = 0;
	while ((c != s[i]) && s[i])
		elm[j++] = s[i++];
	elm[j] = '\0';
	return (elm);
}

char	**ft_split(char *s, char c)
{
	char	**tbl;
	char	*elem;
	int		i;
	int		x;

	if (!s)
		return (0);
	tbl = malloc((ft_wordcount(s, c) + 1) * sizeof(tbl));
	if (!tbl)
		return (0);
	i = 0;
	x = 0;
	while (s[i] && (ft_wordlen(&s[i], c) != 0))
	{
		while ((c == s[i]) && s[i])
			i++;
		elem = malloc((ft_wordlen(&s[i], c) + 1) * sizeof(elem));
		if (!elem)
			return (ft_freetbl(tbl, x));
		tbl[x++] = ft_fillelem(s, c, i, elem);
		while ((c != s[i]) && s[i])
			i++;
	}
	tbl[x] = 0;
	return (tbl);
}
