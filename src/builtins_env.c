/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:07:49 by vladimir          #+#    #+#             */
/*   Updated: 2022/07/25 12:08:29 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

void	builtin_env(int ac, char **env, int fdout)
{
	int		i;
	char	**tbl;

	if (ac == 1)
	{
		i = 0;
		while (env && env[i])
		{
			tbl = ft_split_export(env[i]);
			if (tbl[1] != NULL)
			{
				ft_putstr_fd(env[i], fdout);
				ft_putchar_fd('\n', fdout);
			}
			ft_freetbl(tbl, -1);
			i++;
		}
		ft_free_values_exit(&g_sh, SUCCESS, 1);
	}
	else
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		ft_free_values_exit(&g_sh, FAILURE, 1);
	}
}
