/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:04 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 12:12:58 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

void	process_delimitor(char **delimitor, int	*quotes)
{
	if (str_has_quotes(*delimitor))
	{
		*delimitor = process_quotes_in_delimitor(delimitor);
		*quotes = 1;
	}
}

int	is_delimitor_process(char **tmp, char **delimitor, t_cmd_line **cmd_line)
{
	if (!ft_strncmp(*tmp, *delimitor, ft_strlen(*delimitor))
		&& ft_strlen(*tmp) == ft_strlen(*delimitor))
	{
		ft_putstr_fd("\n", (*cmd_line)->fdin);
		ft_free_null_str(tmp);
		return (1);
	}
	return (0);
}

int	ph(char *delimitor, t_cmd_line **cmd_line, int quotes)
{
	char	*tmp;
	int		i;

	i = 0;
	while (1)
	{
		tmp = read_heredoc_line(cmd_line, quotes, delimitor);
		if (!tmp)
			break ;
		if (is_delimitor_process(&tmp, &delimitor, cmd_line))
			break ;
		write_heredoc_line(&tmp, cmd_line, i);
		i++;
	}
	close((*cmd_line)->fdin);
	return (0);
}

int	wait_heredoc(int pid, int *status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
	{
		if (WEXITSTATUS(*status))
		{
			set_error_exit_status(&g_sh, WEXITSTATUS(*status));
			return (1);
		}
	}
	return (0);
}

int	heredoc(char *dl, t_cmd_line **cmd_line)
{
	int	q;
	int	pid;
	int	status;

	q = 0;
	process_delimitor(&dl, &q);
	if (initialize_heredoc(cmd_line))
		return (1);
	status = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &heredoc_handler);
		ft_free_values_exit(&g_sh, ph(dl, cmd_line, q), 0);
	}
	if (wait_heredoc(pid, &status))
		return (1);
	handle_signals(0);
	close((*cmd_line)->fdin);
	if (q)
		ft_free_null_str(&dl);
	if (open_file_fdin((*cmd_line)->heredoc_name, cmd_line))
		return (1);
	return (0);
}
