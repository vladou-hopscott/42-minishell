/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:02:28 by swillis           #+#    #+#             */
/*   Updated: 2022/04/18 22:53:47 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern char	**environ;

char	*str_exportvalue(char **tbl)
{
	int		i;
	char	*value;

	if (tbl[1] == NULL)
		return (NULL);
	value = ft_strdup(tbl[1]);
	i = 2;
	while (tbl && tbl[i])
	{
		value = ft_strjoin(value, tbl[i]);
		i++;
	}
	return (value);
}

int	main(int ac, char **av)
{
	int		i;
	char	**tbl;
	char	*key;
	char	*value;

	i = 1;
	while (i < ac)
	{
		tbl = ft_split(av[i], '=');
		key = ft_strdup(tbl[0]);
		value = str_exportvalue(tbl);
		environ = env_export(key, value, environ);
		free(key);
		free(value);
		ft_freetbl(tbl, -1);
		i++;
	}
	return (0);
}
