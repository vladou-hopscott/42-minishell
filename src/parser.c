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

	token = (*cmd_line)->token_lst;
	token->type = CMD;
	token = token->next;

	while (token)
	{
		if (token->type == RED_INPUT)
			token->next->type = INPUT;
		else if (token->type == RED_OUTPUT)
			token->next->type = OUTPUT;
		else if (token->type == STR)
			token->type = ARG;
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

//transformation des tokens en list chainee de commandes via le parser
void	parser(t_sh *sh)
{
	printf("PARSER\n\n");

	//1) creation du 1er maillon cmd_line
	//2) tant qu on ne tombe pas sur un pipe, on stock tous les tokens dans la 1ere command line
	//3) quand on tombe sur un pipe, on cree un 2nd maillon cmd_line, et on y fourre tous les tokens suivants jusqu'au prochain pipe
	parse_tokens_in_cmd_lines(sh);

	//derniere phase de tokenisation : remplacement du type STR par le type output/input (ceux qui suivent les redirections)
	update_token_type_str(sh);

	print_tokens(sh->cmd_line_lst->token_lst);
	print_tokens(sh->cmd_line_lst->next->token_lst);

	//4)gestion des quotes et des variables d'environnement : voir en dessous

}

//suppression des quotes qui ne seront pas interpretes dans les tokens STR. Exemple : la commande ***echo "t'" oi*** renvoie ***t oi***
//il faudrait eventuellement rajouter ici l'interpretation du $ dans les double quotes egalement
//interpret_remove_quotes(sh);

