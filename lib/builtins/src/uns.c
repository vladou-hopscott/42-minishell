/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uns.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:02:28 by swillis           #+#    #+#             */
/*   Updated: 2022/04/18 21:09:59 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern char	**environ;

char	**tbl_remove(char **tbl, char *key)
{
	int		i;
	int		pos;
	char	**new;

	pos = env_findkeypos(key, environ);
	if (pos == -1)
		return (tbl);
	new = malloc(sizeof(char *) * (ft_tbllen(tbl)));
	if (!new)
		return (tbl);
	i = 0;
	while (tbl && tbl[i])
	{
		if (i != pos)
			new[i] = ft_strdup(tbl[i]);
		i++;
	}
	new[i] = NULL;
	ft_freetbl(tbl, -1);
	return (new);
}

int	main(int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		environ = tbl_remove(environ, av[i]);
		i++;
	}
	return (0);
}
