/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:24 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 14:36:45 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*choose_filename(void)
{
	char	*filename;
	int		file_exists;
	int		i;
	char	*nbr;

	i = 1;
	filename = ft_strdup("./.heredoc");
	file_exists = open(filename, O_RDONLY);
	while (file_exists != -1)
	{
		close(file_exists);
		nbr = ft_itoa(i);
		filename = ft_strjoin_free(&filename, &nbr);
		file_exists = open(filename, O_RDONLY);
		i++;
	}
	if (file_exists != -1)
		close(file_exists);
	return (filename);
}

int	initialize_heredoc(t_cmd_line **cmd_line)
{
	ft_free_null_str(&(*cmd_line)->heredoc_name);
	(*cmd_line)->heredoc_name = choose_filename();
	(*cmd_line)->heredoc_mode = 1;
	(*cmd_line)->fdin = open((*cmd_line)->heredoc_name,
			O_RDWR | O_CREAT | O_APPEND, 00644);
	if ((*cmd_line)->fdin == -1)
		return (1);
	return (0);
}

void	write_heredoc_line(char **tmp, t_cmd_line **cmd_line, int i)
{
	if (i > 0)
		ft_putstr_fd("\n", (*cmd_line)->fdin);
	ft_putstr_fd(*tmp, (*cmd_line)->fdin);
	ft_free_null_str(tmp);
}
