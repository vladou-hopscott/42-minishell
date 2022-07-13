/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:04 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/13 15:46:56 by vladimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

char	*trim_quotes_in_delimitor(char **value, int *i, int *j)
{
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	s1 = ft_strndup(&(*value)[*j], *i - *j);
	*i = *i + 1;
	*j = *i;
	while ((*value)[*i] && (*value)[*i] != SINGLE_QUOTE
			&& (*value)[*i] != DOUBLE_QUOTE)
		*i = *i + 1;
	if ((*value)[*i] == SINGLE_QUOTE || (*value)[*i] == DOUBLE_QUOTE)
		s2 = ft_strndup(&(*value)[*j], *i - *j);
	*j = *i + 1;
	return (ft_strjoin_free(&s1, &s2));
}

char	*process_quotes_in_delimitor(char **value)
{
	char	*new;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = NULL;
	while ((*value)[i])
	{
		if ((*value)[i] == SINGLE_QUOTE || (*value)[i] == DOUBLE_QUOTE)
		{
			temp = trim_quotes_in_delimitor(value, &i, &j);
			new = ft_strjoin_free(&new, &temp);
		}
		i++;
	}
	temp = ft_strndup(&(*value)[j], i - j);
	return (ft_strjoin_free(&new, &temp));
}

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

int	process_heredoc(char *delimitor, t_cmd_line **cmd_line, int quotes)
{
	char	*tmp;
	int		i;

	i = 0;
	while (1)
	{
		tmp = read_heredoc_line(cmd_line, quotes, delimitor);
		if (!tmp)
			break;
		if (is_delimitor_process(&tmp, &delimitor, cmd_line))
			break ;
		write_heredoc_line(&tmp, cmd_line, i);
		i++;
	}
	close((*cmd_line)->fdin);
	return (0);
}

int	heredoc(char *delimitor, t_cmd_line **cmd_line)
{
	int	quotes;
	int	pid;
	int	status;

	quotes = 0;
	process_delimitor(&delimitor, &quotes);
	if (initialize_heredoc(cmd_line))
		return (1);
	status = 0;	
	pid = fork();
	if (pid == 0)
		exit(process_heredoc(delimitor, cmd_line, quotes));
	if (waitpid(pid, &status, 0) < 0 && WIFEXITED(status))
	{
		set_error_exit_status(&g_sh, WEXITSTATUS(status));
		return (1);
	}
	close((*cmd_line)->fdin);
	if (open_file_fdin((*cmd_line)->heredoc_name, cmd_line))
		return (1);
	return (0);
}

//int	heredoc(char *delimitor, t_cmd_line **cmd_line)
//{
//	char	*tmp;
//	int		i;
//	int		quotes;

//	quotes = 0;
//	process_delimitor(&delimitor, &quotes);
//	if (initialize_heredoc(cmd_line))
//		return (1);
//	i = 0;
//	while (1)
//	{
//		tmp = read_heredoc_line(cmd_line, quotes, delimitor);
//		if (!tmp)
//			return (1);
//		if (is_delimitor_process(&tmp, &delimitor, cmd_line))
//			break ;
//		write_heredoc_line(&tmp, cmd_line, i);
//		i++;
//	}
//	close((*cmd_line)->fdin);
//	if (open_file_fdin((*cmd_line)->heredoc_name, cmd_line))
//		return (1);
//	return (0);
//}
