/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:54:59 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/21 14:45:17 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

int	process_eof_heredoc(char **tmp, t_cmd_line **cmd_line)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", 1);
	ft_putstr_fd("\n", (*cmd_line)->fdin);
	ft_free_null_str(tmp);
	return (1);
}

char	*delimit_envvar_heredoc(char *str)
{
	int		i;
	char	*env_key;

	env_key = NULL;
	i = 1;
	if (ft_isdigit(str[i]))
		return (NULL);
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	env_key = ft_strndup(str + 1, i - 1);
	return (env_key);
}

char	*expand_envvar_in_heredoc(char *str, int *i, int *j, char **s1)
{
	char	*env_key;
	char	*env_val;
	char	*tmp;

	env_key = NULL;
	env_val = NULL;
	if (!ft_strncmp(str, "$$", 2))
	{
		tmp = *s1;
		*s1 = ft_strjoin(*s1, "$");
		ft_free_null_str(&tmp);
		*i = *i + 1;
		*j = *i;
		return (*s1);
	}
	env_key = delimit_envvar_heredoc(str);
	if (env_key && env_key[0] == '\0')
		env_val = ft_strdup("$");
	else
		env_val = env_findkeyvalue(env_key, g_sh.env);
	if (!env_key)
		*i = *i + 1;
	*i = *i + ft_strlen(env_key);
	*j = *i + 1;
	if (env_val)
		*s1 = ft_strjoin_free(s1, &env_val);
	ft_free_null_str(&env_key);
	return (*s1);
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
