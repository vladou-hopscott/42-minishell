#include "minishell.h"

void	parse_tokens_in_cmd_lines(t_sh *sh)
{
	t_token		*token;
	t_cmd_line	*start;

	token = sh->token_lst;
	sh->cmd_line_lst = add_back_cmd_line(sh->cmd_line_lst);
	start = sh->cmd_line_lst;
	while (token)
	{
		if (token->type != PIPE)
			sh->cmd_line_lst->token_lst = add_back_token(sh->cmd_line_lst->token_lst, token->type, token->value);
		else
		{
			sh->cmd_line_lst = add_back_cmd_line(sh->cmd_line_lst);
			sh->cmd_line_lst = sh->cmd_line_lst->next;
		}
		token = token->next;
	}
	sh->cmd_line_lst = start;
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

void	update_elems_cmd_lines(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		update_cmd(&sh->cmd_line_lst);
		update_args(&sh->cmd_line_lst);

		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

//transformation des tokens en list chainee de commandes via le parser
void	parser(t_sh *sh)
{
	printf("PARSER\n\n");

	//1) parsing des tokens en commande lines. chaque commande line est separee par un pipe. pour l'instant on stocke les tokens dans les commandes lines
	parse_tokens_in_cmd_lines(sh);

	//2)derniere phase de tokenisation : remplacement du type STR par CMD, ARG, INPUTS ou OUTPUTS
	update_token_type_str(sh);
	//A rajouter eventuellement : modifier les tokens CMD en token BUILTIN quand on reconnait un str correspondant a une fonction builtin

	//print tokens
	t_cmd_line *temp;
	temp = sh->cmd_line_lst;
	while (temp)
	{
		print_tokens(temp->token_lst);
		temp = temp->next;
	}

	//3)Ajout de tous les autres elements necessaires dans les structures commande line
	update_elems_cmd_lines(sh);

	//print cmds & args
	temp = sh->cmd_line_lst;
	while (temp)
	{
		printf("cmd=%s\n",temp->cmd);
		int i = 0;
		printf("args: ");
		while (temp->args[i])
		{
			printf("[%s] ", temp->args[i]);
			i++;
		}
		printf("\n\n");
		temp = temp->next;
	}

	//4)gestion des quotes et des variables d'environnement : voir en dessous
}

//suppression des quotes qui ne seront pas interpretes dans les tokens STR. Exemple : la commande ***echo "t'" oi*** renvoie ***t oi***
//il faudrait eventuellement rajouter ici l'interpretation du $ dans les double quotes egalement
//interpret_remove_quotes(sh);
