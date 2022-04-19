/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:02:28 by swillis           #+#    #+#             */
/*   Updated: 2022/04/19 17:21:57 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int ac, char **av)
{
	int	i;
	int	ntrail;

	ntrail = 1;
	i = 1;
	while (ft_strncmp(av[i], "-n", (ft_strlen("-n") + 1)) == 0)
	{
		ntrail = 0;
		i++;
	}
	if (i < ac)
		ft_putstr(av[i++]);
	while (i < ac)
	{
		ft_putchar(' ');
		ft_putstr(av[i++]);
	}
	if (ntrail)
		ft_putchar('\n');
	return (0);
}
