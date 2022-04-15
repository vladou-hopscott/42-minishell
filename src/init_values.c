
#include "minishell.h"

void	init_values(t_sh *sh)
{
	sh->token_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
	sh->p_quote = NO_QUOTE;
}

void	free_token_lst(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

void	free_values(t_sh *sh)
{
	free_token_lst(sh->token_lst);
	free(sh->prompt);
	ft_freetbl(sh->env, -1);
}