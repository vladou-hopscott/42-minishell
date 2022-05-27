#include "minishell.h"

extern char	**environ;

t_token	*tokenize_within_token(t_token **token)
{
	if (!str_has_space_without_quotes((*token)->value))
		return (*token);
	return (create_tokens_within_tokens(token, (*token)->value));
}

t_token	*create_tokens_within_tokens(t_token **token, char *str)
{
	int		i;
	int		j;
	int		quote_status;

	quote_status = NO_QUOTE;
	i = 0;
	j = 0;
	while (str[i])
	{
		quote_status = check_quote_status_in_str(str[i], quote_status);
		if (quote_status == NO_QUOTE && str[i] == ' ')
		{
			if (j == 0)
				(*token)->value = ft_strndup(str, i);
			else
				*token = add_middle_token(
						(*token), STR, ft_strndup(&str[j], i - j));
			j = i + 1;
		}
		i++;
	}
	if (i > j)
		*token = add_middle_token((*token), STR, ft_strndup(&str[j], i - j));
	return (*token);
}

void	expand_envvars_in_tokens(t_cmd_line **cmd_line)
{
	t_token	*token;
	char	*new_value;
	char	*temp;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == STR)
		{
			new_value = expand_envvars_in_token(&token->value);
			if (new_value)
			{
				temp = token->value;
				token->value = new_value;
				ft_free_null_str(&temp);
			}
		}
		token = token->next;
	}
}

void	update_tokens(t_cmd_line **cmd_line)
{
	t_token		*token;
	int			has_cmd;

	token = (*cmd_line)->token_lst;
	has_cmd = 0;
	while (token)
	{
		if (token->type == RED_INPUT)
			token->next->type = INPUT;
		else if (token->type == RED_OUTPUT)
			token->next->type = OUTPUT;
		else if (token->type == RED_APPEND)
			token->next->type = OUTPUT_APPEND;
		else if (token->type == HEREDOC)
			token->next->type = HEREDOC_LIMIT;
		else if (token->type == STR)
		{
			if (!has_cmd)
			{
				token->type = CMD;
				has_cmd = 1;
			}
			else
				token->type = ARG;
		}
		token = token->next;
	}
}

void	update_token_type_str(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		update_tokens(&sh->cmd_line_lst);
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

void	update_tokens_hd_limit(t_cmd_line **cmd_line)
{
	t_token		*token;
	int			has_cmd;

	token = (*cmd_line)->token_lst;
	has_cmd = 0;
	while (token)
	{
		if (token->type == HEREDOC)
			token->next->type = HEREDOC_LIMIT;
		token = token->next;
	}
}

void	update_token_type_heredoc_limit(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		update_tokens_hd_limit(&sh->cmd_line_lst);
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

void	process_quotes_in_tokens(t_cmd_line **cmd_line)
{
	t_token	*token;
	char	*new_value;
	char	*temp;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == STR)
		{
			new_value = process_quotes_in_token(&token->value);
			if (new_value)
			{
				temp = token->value;
				token->value = new_value;
				ft_free_null_str(&temp);
			}
		}
		token = token->next;
	}
}
