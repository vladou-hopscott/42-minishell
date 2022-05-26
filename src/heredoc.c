/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:45:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/26 14:36:09 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//A RAJOUTER : GESTION DES QUOTES ET DES EXPANDS
int	heredoc(char *delimitor, t_cmd_line ** cmd_line)
{
	char	*tmp;
	int		i;

	(*cmd_line)->heredoc_mode = 1;
	(*cmd_line)->fdin = open("./heredoc", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	i = 0;
	while (1)
	{
		tmp = readline("> ");
		if (!ft_strncmp(tmp, delimitor, ft_strlen(delimitor)) && ft_strlen(tmp) == ft_strlen(delimitor))
		{
			ft_free_null_str(&tmp);
			break;
		}
		if (i > 0)
			ft_putstr_fd("\n", (*cmd_line)->fdin);
		ft_putstr_fd(tmp, (*cmd_line)->fdin);
		ft_free_null_str(&tmp);
		i++;
	}
	return (0);
}
