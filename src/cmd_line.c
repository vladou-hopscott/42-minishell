#include "minishell.h"
#include "parsing.h"

void	update_cmd(t_cmd_line **cmd_line)
{
	t_token	*token;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == CMD)
		{
			(*cmd_line)->cmd = ft_strdup(token->value);
			return;
		}
		token = token->next;
	}
}

void	update_args(t_cmd_line **cmd_line)
{
	t_token	*token;
	int		i;

	token = (*cmd_line)->token_lst;
	(*cmd_line)->args = ft_calloc(count_arg_tokens(token) + 1, sizeof(char *));
	if (!(*cmd_line)->args)
		return;
	i = 0;
	while (token)
	{
		if (token->type == ARG)
		{
			(*cmd_line)->args[i] = ft_calloc(ft_strlen(token->value) + 1, sizeof(char));
			if (!(*cmd_line)->args[i])
				return; //need to free all table
			(*cmd_line)->args[i] = ft_strdup(token->value);
			i++;
		}
		token = token->next;
	}
	(*cmd_line)->args[i] = NULL;
}
