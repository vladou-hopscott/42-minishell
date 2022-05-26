/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:45:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/26 12:05:47 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//A RAJOUTER : GESTION DES QUOTES ET DES EXPANDS
int	heredoc(char *delimitor, t_cmd_line ** cmd_line)
{
	char	*tmp;

	(*cmd_line)->heredoc_mode = 1;
	(*cmd_line)->fdin = open("./heredoc", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	while (1)
	{
		tmp = readline("> ");
		if (!ft_strncmp(tmp, delimitor, ft_strlen(delimitor)) && ft_strlen(tmp) == ft_strlen(delimitor))
			break;
		ft_putstr_fd("\n", (*cmd_line)->fdin);
		ft_putstr_fd(tmp, (*cmd_line)->fdin);
	}
	return (0);
}

//close((*cmd_line)->fdin);
