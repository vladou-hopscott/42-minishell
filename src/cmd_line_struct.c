#include "minishell.h"

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
		if (token->type == CMD || token->type == ARG)
		{
			//(*cmd_line)->args[i] = ft_calloc(ft_strlen(token->value) + 1, sizeof(char));
			(*cmd_line)->args[i] = ft_strndup(token->value, ft_strlen(token->value));
			if (!(*cmd_line)->args[i])
				return;
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
			if ((*cmd_line)->fdout != 1)
				close((*cmd_line)->fdout);
			if (token->type == OUTPUT)
			{
				(*cmd_line)->fdout = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				(*cmd_line)->append_mode = 0;
			}
			else
			{
				(*cmd_line)->fdout = open(token->value, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				(*cmd_line)->append_mode = 1;
			}
			//A RAJOUTER : gestion d'erreur si la fct open fail
			// if ((*cmd_line)->fdout == -1)
				//gestion erreur
		}
		token = token->next;
	}

}

//while loop through tokens
//on cherche si 1 fichier de redirection d'entree existe. si oui, on l'ouvre en read only, et ca devient le fdin
//on continue a chercher. si d'autres se presentent : on ferme (close) le precedent, le nouveau devient le nouveau fd, etc
int	update_fdin(t_cmd_line **cmd_line)
{
	t_token	*token;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == INPUT || token->type == HEREDOC_LIMIT)
		{
			if ((*cmd_line)->fdin != 0)
				close((*cmd_line)->fdin);
			if ((*cmd_line)->heredoc_mode == 1)
			{
				(*cmd_line)->heredoc_mode = 0;
				unlink("./heredoc");
			}
			if (token->type == INPUT)
			{
				if (token->type == INPUT)
					(*cmd_line)->fdin = open(token->value, O_RDONLY);
				if ((*cmd_line)->fdin == -1)
				{
					ft_putstr_fd("bash: ", 2);
					ft_putstr_fd(token->value, 2);
					ft_putstr_fd(": No such file or directory\n", 2);
					return (1);
				}
			}
			else
				heredoc(token->value, cmd_line);
		}
		token = token->next;
	}
	return (0);
}

void	update_elems_cmd_lines(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		update_cmd(&sh->cmd_line_lst);
		update_args(&sh->cmd_line_lst);
		update_fdout(&sh->cmd_line_lst);
		if (update_fdin(&sh->cmd_line_lst))
			sh->error = 1;
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
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

