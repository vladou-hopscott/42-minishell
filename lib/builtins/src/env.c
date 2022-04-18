/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:02:28 by swillis           #+#    #+#             */
/*   Updated: 2022/04/18 22:51:38 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern char	**environ;

int	main(int ac, char **av)
{
	int		i;

	(void)av;
	if (ac != 1)
	{
		perror("env: too many arguments");
		return (-1);
	}
	i = 0;
	while (environ && environ[i])
	{
		ft_putstr(environ[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}
