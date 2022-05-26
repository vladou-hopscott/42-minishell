/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:45:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/26 22:50:16 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char *choose_filename(void)
{
	char	*filename;
	int		file_exists;
	int		i;
	char	*nbr;

	i = 1;
	filename = ft_strdup("./heredoc");
	file_exists = open(filename, O_RDONLY);
	while (file_exists != -1)
	{
		close(file_exists);
		nbr = ft_itoa(i);
		filename = ft_strjoin_free(&filename, &nbr);
		file_exists = open(filename, O_RDONLY);
		i++;
	}
	close(file_exists);
	return (filename);
}

//CTR+C => A voir si il faut vraiment le faire (ca a l'air tres relou)
//A RAJOUTER : GESTION DES QUOTES ET DES EXPANDS
int	heredoc(char *delimitor, t_cmd_line ** cmd_line)
{
	char	*tmp;
	int		i;

	(*cmd_line)->heredoc_name = choose_filename();
	(*cmd_line)->heredoc_mode = 1;
	(*cmd_line)->fdin = open((*cmd_line)->heredoc_name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if ((*cmd_line)->fdin == -1)
		return (1);
	i = 0;
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			ft_putstr_fd("bash: warning: here-document delimited by end-of-file\n", 1);
			ft_free_null_str(&tmp);
			close((*cmd_line)->fdin);
			unlink((*cmd_line)->heredoc_name);
			ft_free_null_str(&(*cmd_line)->heredoc_name);
			return(1);
		}
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
