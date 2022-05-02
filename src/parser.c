#include "minishell.h"

void	parse_tokens_in_cmd_lines(t_sh *sh)
{
	t_token		*token;
	t_cmd_line	*cmd_line;

	token = sh->token_lst;
	cmd_line = add_back_cmd_line(sh->cmd_line_lst);
	while (token)
	{
		while (token && token->type != PIPE)
		{
			cmd_line->token_lst = add_back_token(cmd_line->token_lst, token->type, token->value);
			if (token->next)
				token = token->next;
			else
				break;
		}
		if (token && token->type == PIPE)
		{
			cmd_line = add_back_cmd_line(cmd_line);
			cmd_line = cmd_line->next;
		}
		if (token->next)
			token = token->next;
		else
			break;
	}
}

// void	update_token_type_str(t_sh *sh)
// {
// 	t_token	tmp;
// }

//transformation des tokens en list chainee de commandes via le parser
void	parser(t_sh *sh)
{
	printf("PARSER\n\n");

	//1) creation du 1er maillon cmd_line
	//2) tant qu on ne tombe pas sur un pipe, on stock tous les tokens dans la 1ere command line
	//3) quand on tombe sur un pipe, on cree un 2nd maillon cmd_line, et on y fourre tous les tokens suivants jusqu'au prochain pipe
	parse_tokens_in_cmd_lines(sh);

	//derniere phase de tokenisation : remplacement du type STR par le type output/input (ceux qui suivent les redirections)
	//update_token_type_str(sh);

	// while (sh->cmd_line_lst)
	// print_tokens(cmd_line->token_lst);
	// printf("\n\n");


	//4)gestion des quotes et des variables d'environnement : voir en dessous

}

//suppression des quotes qui ne seront pas interpretes dans les tokens STR. Exemple : la commande ***echo "t'" oi*** renvoie ***t oi***
//il faudrait eventuellement rajouter ici l'interpretation du $ dans les double quotes egalement
//interpret_remove_quotes(sh);

