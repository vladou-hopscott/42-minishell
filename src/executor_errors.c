/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:22 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/23 16:18:54 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_cmd_not_found(t_sh *sh, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	sh->error = 1;
	sh->exit_status = CMD_NOT_FOUND;
	if (sh->has_pipe)
		exit(CMD_NOT_FOUND);
}

void	err_export_invalid(t_sh *sh, char *key)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	sh->error = 1;
	sh->exit_status = FAILURE;
	if (sh->has_pipe)
		exit(FAILURE);
}

void	err_unset_invalid(t_sh *sh, char *key)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	sh->error = 1;
	sh->exit_status = FAILURE;
	if (sh->has_pipe)
		exit(FAILURE);
}

void	err_exit_invalid(t_sh *sh, char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	sh->error = 1;
	sh->exit_status = MAJOR_FAILURE;
	ft_free_values_exit(sh, MAJOR_FAILURE);
}
