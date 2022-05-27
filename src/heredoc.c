/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:45:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/27 15:33:09 by vnafissi         ###   ########.fr       */
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

char	*expand_envvars_in_heredoc(char **value)
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;
	int		quote_status;

	i = 0;
	j = 0;
	s1 = NULL;
	quote_status = NO_QUOTE;
	while ((*value)[i])
	{
		//quote_status = check_quote_status_in_str((*value)[i], quote_status);
		//if (quote_status == NO_QUOTE && (*value)[i] == '$')
		if ((*value)[i] == '$')
		{
			s2 = ft_strndup(&(*value)[j], i - j); //on enregistre ce qu'il y a avant le $
			s1 = ft_strjoin_free(&s1, &s2); //on join ca a s1
			s1 = expand_envvar(&(*value)[i], &i, &j, &s1, quote_status);
		}
		i++;
	}
	s2 = ft_strndup(&(*value)[j], i - j); 	//join last part of string to new
	return (ft_strjoin_free(&s1, &s2));
}

char	*expand_heredoc_line(char **str)
{
	char	*tmp;

	tmp = expand_envvars_in_heredoc(str);

	//ft_free_null_str(str);

	return (tmp);
}

int	process_eof_heredoc(char **tmp, t_cmd_line ** cmd_line)
{
	ft_putstr_fd("bash: warning: here-document delimited by end-of-file\n", 1);
	ft_free_null_str(tmp);
	close((*cmd_line)->fdin);
	unlink((*cmd_line)->heredoc_name);
	ft_free_null_str(&(*cmd_line)->heredoc_name);
	return (1);
}

void	initialize_heredoc(t_cmd_line **cmd_line)
{
	(*cmd_line)->heredoc_name = choose_filename();
	(*cmd_line)->heredoc_mode = 1;
	(*cmd_line)->fdin = open((*cmd_line)->heredoc_name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

char	*read_heredoc_line(t_cmd_line **cmd_line, int quotes)
{
	char	*str;

	str = readline("> ");
	if (!str)
	{
		process_eof_heredoc(&str, cmd_line);
		return (NULL);
	}
	if (!quotes && str_has_charset(str, "$"))
		str = expand_heredoc_line(&str);
	return (str);
}

//CTR+C => A voir si il faut vraiment le faire (ca a l'air tres relou)
//A RAJOUTER : GESTION DES QUOTES ET DES EXPANDS
	//heredoc_limit token must never be expanded
	//check if there are quotes in heredoc_limit token
	//if so,
		//set counter no expansion
		//remove quotes from heredoc_limit token
	//Else set specific rule in readline to expand env vars like regular env expansion
int	heredoc(char *delimitor, t_cmd_line ** cmd_line)
{
	char	*tmp;
	int		i;
	int		quotes;

	quotes = 0;
	if (str_has_quotes(delimitor))
	{
		delimitor = process_quotes_in_token(&delimitor);
		quotes = 1;
	}
	initialize_heredoc(cmd_line);
	if ((*cmd_line)->fdin == -1)
		return (1);
	i = 0;
	while (1)
	{
		tmp = read_heredoc_line(cmd_line, quotes);
		if (!tmp)
			return(1);
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
