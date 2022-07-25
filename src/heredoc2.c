/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:54:59 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 16:27:30 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_eof_heredoc(char **tmp, t_cmd_line **cmd_line)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n",
		1);
	ft_putstr_fd("\n", (*cmd_line)->fdin);
	ft_free_null_str(tmp);
	return (1);
}

char	*expand_envvars_in_heredoc(char **value)
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s1 = NULL;
	while ((*value)[i])
	{
		if ((*value)[i] == '$')
		{
			s2 = ft_strndup(&(*value)[j], i - j);
			s1 = ft_strjoin_free(&s1, &s2);
			s1 = expand_envvar_in_heredoc(&(*value)[i], &i, &j, &s1);
		}
		i++;
	}
	s2 = ft_strndup(&(*value)[j], i - j);
	return (ft_strjoin_free(&s1, &s2));
}

char	*expand_heredoc_line(char **str)
{
	char	*tmp;

	tmp = expand_envvars_in_heredoc(str);
	ft_free_null_str(str);
	return (tmp);
}

char	*read_heredoc_line(t_cmd_line **cmd_line, int quotes, char *delimitor)
{
	char	*str;

	str = readline("> ");
	if (!str)
	{
		process_eof_heredoc(&str, cmd_line);
		return (NULL);
	}
	if (!quotes)
	{
		if (!ft_strncmp(str, delimitor, ft_strlen(delimitor))
			&& ft_strlen(str) == ft_strlen(delimitor))
			return (str);
		else if (str_has_charset(str, "$"))
			str = expand_heredoc_line(&str);
	}
	return (str);
}
