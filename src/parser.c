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
		update_fdout(&sh->cmd_line_lst); //update fdout and create/truncate files if needed
		update_fdin(&sh->cmd_line_lst); //update fdin
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

void	process_quotes_in_cmd_lines(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		process_quotes_in_tokens(&sh->cmd_line_lst);
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

//transformation des tokens en list chainee de commandes via le parser
void	parser(t_sh *sh)
{
	parse_tokens_in_cmd_lines(sh);//chaque commande line est separee par un pipe
	//A rajouter : fonction pour remplir cmd_line->str avant d'enlever quotes et autres
	//A RAJOUTER : avant les quotes, il faut expand ls variables d'env qui n'ont pas de quotes
	// expand_envvar_without_quotes(sh);
	process_quotes_in_cmd_lines(sh);// a voir si on met pas ca dans le lexer au lieu du parser
	update_token_type_str(sh); //remplacement du type STR par CMD, ARG, INPUTS ou OUTPUTS
	//A rajouter eventuellement : modifier les tokens CMD en token BUILTIN quand on reconnait un str correspondant a une fonction builtin
	update_elems_cmd_lines(sh);//Ajout de fdin, fdout, cmd & args dans les structures commande line

	//for each cmd line structure, print tokens, cmd, args, fdin, fdout
	t_cmd_line *temp;
	temp = sh->cmd_line_lst;
	while (temp)
	{
		printf("tokens : \n");
		print_tokens(temp->token_lst);
		printf("cmd=%s\n",temp->cmd);
		int i = 0;
		printf("args: [");
		while (temp->args[i])
		{
			printf("%s,", temp->args[i]);
			i++;
		}
		printf("]");
		printf("\nfdout=%d, fdin=%d\n", temp->fdout, temp->fdin);
		printf("\n\n");
		temp = temp->next;
	}
}
