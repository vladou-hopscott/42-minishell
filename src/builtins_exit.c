/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:07 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 12:04:23 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

void	builtin_exit(int ac, char **av)
{
	if (ac == 1)
	{
		if (!g_sh.has_pipe)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_free_values_exit(&g_sh, g_sh.exit_status, 1);
	}
	else
	{
		if (str_is_long_long(av[1]))
		{
			if (ac > 2)
			{
				if (!g_sh.has_pipe)
					ft_putstr_fd("exit\n", STDOUT_FILENO);
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				set_error_exit_status(&g_sh, FAILURE);
				if (g_sh.has_pipe)
					ft_free_values_exit(&g_sh, FAILURE, 1);
			}
			else
				ft_free_values_exit(&g_sh, ft_atoll(av[1]), 1);
		}
		else
			err_exit_invalid(&g_sh, av[1]);
	}
}
