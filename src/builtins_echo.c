/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:07 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 11:38:46 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

int	find_first_arg_to_print(int ac, char **av, int *ntrail)
{
	int	i;
	int	j;

	i = 1;
	while ((i < ac) && (av[i][0] == '-'))
	{
		j = 1;
		while (av[i][j] == 'n')
			j++;
		if (j != (int)ft_strlen(av[i]))
			break ;
		*ntrail = 0;
		i++;
	}
	return (i);
}

void	builtin_echo(int ac, char **av, int fdout)
{
	int	i;
	int	ntrail;

	ntrail = 1;
	i = find_first_arg_to_print(ac, av, &ntrail);
	if (i < ac)
		ft_putstr_fd(av[i++], fdout);
	while (i < ac)
	{
		ft_putchar_fd(' ', fdout);
		ft_putstr_fd(av[i++], fdout);
	}
	if (ntrail)
		ft_putchar_fd('\n', fdout);
	ft_free_values_exit(&g_sh, SUCCESS, 1);
}
