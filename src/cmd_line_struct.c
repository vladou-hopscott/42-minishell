#include "minishell.h"
#include "parsing.h"

void	process_quotes_in_tokens(t_cmd_line **cmd_line)
{
	t_token	*token;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == STR)
		{
			process_quotes_in_token(&token);
		}
		token = token->next;
	}
}

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
		if (token->type == OUTPUT || token->type == OUTPUT_APPEND)
		{
			// if there is already a fd opened (different from initial value standard output), close it
			if ((*cmd_line)->fdout != 1)
				close((*cmd_line)->fdout);
			// open and erase content or create file. update cmd_line->fdout
			if (token->type == OUTPUT)
				(*cmd_line)->fdout = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			else
				(*cmd_line)->fdout = open(token->value, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			//A RAJOUTER : gestion d'erreur si la fct open fail
			// if ((*cmd_line)->fdout == -1)
				//gestion erreur
		}
		token = token->next;
	}
}

void	update_fdin(t_cmd_line **cmd_line)
{
	//while loop through tokens
	//on cherche si 1 fichier de redirection d'entree existe. si oui, on l'ouvre en read only, et ca devient le fdin
	//on continue a chercher. si d'autres se presentent : on ferme (close) le precedent, le nouveau devient le nouveau fd, etc
	t_token	*token;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == INPUT)
		{
			// if there is already a fd opened (different from initial value standard output), close it
			if ((*cmd_line)->fdin != 0)
				close((*cmd_line)->fdin);
			// open file in read only. update cmd_line->fdin
			if (token->type == INPUT)
				(*cmd_line)->fdin = open(token->value, O_RDONLY);
			//A RAJOUTER : gestion d'erreur si la fct open fail, par exemple si le fichier n'existe pas ?
			//A RAJOUTER : gestion des heredocs
			if ((*cmd_line)->fdin == -1)
				printf("fdin : file '%s' does not exist, cannot be opened\n", token->value);
		}
		token = token->next;
	}
}

//MODE ARGUMENT OF OPEN FUNCTION : need to check which modes have to be applied
// S_IRWXU  00700 user (file owner) has read, write, and execute permission
// S_IRUSR  00400 user has read permission
// S_IWUSR  00200 user has write permission
// S_IXUSR  00100 user has execute permission
// S_IRWXG  00070 group has read, write, and execute permission
// S_IRGRP  00040 group has read permission
// S_IWGRP  00020 group has write permission
// S_IXGRP  00010 group has execute permission
// S_IRWXO  00007 others have read, write, and execute permission
// S_IROTH  00004 others have read permission
// S_IWOTH  00002 others have write permission
// S_IXOTH  00001 others have execute permission
