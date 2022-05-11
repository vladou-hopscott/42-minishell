#include "minishell.h"

int is_redirection(t_token_type type)
{
    if (type == RED_INPUT
		|| type == RED_OUTPUT
        || type == HEREDOC
        || type == RED_APPEND)
        return (1);
    return (0);
}

int	error_next_is_pipe(t_token *token)
{
	if (token->type == PIPE)
	{
		printf("bash: syntax error near unexpected token '|'\n");
		return (1);
	}
	return (0);
}

int	error_next_is_null(t_token *token)
{
	if (token == NULL)
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		return (1);
	}
	return (0);
}

int	error_next_is_redirection(t_token *token)
{
	char	*err;

	err=NULL;
	if (token->type == RED_INPUT)
		err="<";
	else if (token->type == RED_OUTPUT)
		err=">";
	else if (token->type == HEREDOC)
		err="<<";
	else if (token->type == RED_APPEND)
		err=">>";
	if (err)
	{
		printf("bash: syntax error near unexpected token '");
		printf("%s", err);
		printf("'\n");
		return (1);
	}
	return (0);
}

int check_syntax_errors(t_sh *sh)
{
    t_token *token;

    token = sh->token_lst;
    while (token)
    {
        if (is_redirection(token->type))
        {
            if (error_next_is_null(token->next))
				return (1);
			else if (error_next_is_pipe(token->next))
				return (1);
			else if (error_next_is_redirection(token->next))
				return (1);
        }
		else if (token->type == PIPE)
		{
			if (error_next_is_null(token->next))
				return (1);
			else if (error_next_is_pipe(token->next))
				return (1);
		}
        token = token->next;
    }
    return (0);
}
