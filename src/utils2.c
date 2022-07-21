/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:51:21 by vladimir          #+#    #+#             */
/*   Updated: 2022/07/21 19:23:51 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_check(int fd, char *filename)
{
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		if (errno == 13)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (errno == 2)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": An error occured\n", 2);
		return (1);
	}
	return (0);
}

int	ft_str_tbl_len(char **tbl)
{
	int	i;

	if (!tbl)
		return (0);
	i = 0;
	while (tbl[i])
		i++;
	return (i);
}

void	set_error_exit_status(t_sh *sh, int status)
{
	sh->exit_status = status;
	sh->error = 1;
}
