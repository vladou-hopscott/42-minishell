/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:55:00 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/21 18:55:14 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(t_cmd_line *cmdl, int status, t_sh *sh)
{
	if ((cmdl->pid != -1) && (0 < waitpid(cmdl->pid, &status, 0)))
	{
		set_error_exit_status(sh, WEXITSTATUS(status));
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
			{
				set_error_exit_status(sh, 130);
				ft_putstr_fd("\n", 1);
			}
			else if (WTERMSIG(status) == 3)
			{
				ft_putstr_fd("Quit (core dumped)\n", 2);
				set_error_exit_status(sh, 131);
			}
		}
	}
}
