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

void	update_fdout(t_cmd_line **cmd_line)
{
	//while loop through tokens
	//on cherche si 1 fichier de redirection de sortie existe. si oui, on l'ouvre/cree, on ecrase son contenu ou on append, et ca devient le fdout
	//on continue a chercher. si d'autres se presentent : on ferme (close) le precedent, le nouveau devient le nouveau fd, etc

	t_token	*token;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == OUTPUT) //need to handle case APPEND too
		{
			// if there is already a fd opened (different from initial value standard output), close it
			if ((*cmd_line)->fdout != 1)
				close((*cmd_line)->fdout);
			// open and erase content or create file. update cmd_line->fdout
			(*cmd_line)->fdout = open(token->value, O_RDWR | O_CREAT | O_TRUNC);
			//ATTENTION need to check if permissions on file have to be changed
		}
		token = token->next;
	}
}
