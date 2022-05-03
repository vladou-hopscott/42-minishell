#include "minishell.h"
#include "parsing.h"

void	update_cmd(t_cmd_line **cmd_line)
{
	(*cmd_line)->cmd = ft_strdup((*cmd_line)->token_lst->value);
}

void	update_args(t_cmd_line **cmd_line)
{
	t_token	*token;
	int		count_args;
	int		len;
	int		i;

	count_args = list_length((*cmd_line)->token_lst);
	(*cmd_line)->args = ft_calloc(count_args + 1, sizeof(char *));
	if (!(*cmd_line)->args)
		return;

	token = (*cmd_line)->token_lst;
	if (token)
		token = token->next;

	i = 0;
	while (token)
	{
		len = ft_strlen(token->value);
		(*cmd_line)->args[i] = ft_calloc(len + 1, sizeof(char));
		if (!(*cmd_line)->args[i])
			return; //need to free all table
		(*cmd_line)->args[i] = ft_strdup(token->value);
		i++;
		token = token->next;
	}
	(*cmd_line)->args[i] = NULL;
}
