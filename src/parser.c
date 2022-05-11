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

void	expand_envvars_without_quotes(t_sh *sh)
{
	t_cmd_line	*start;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		expand_envvars_in_tokens(&sh->cmd_line_lst);
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;
}

void	tokenize_after_env_exp(t_sh *sh)
{
	t_cmd_line	*start;
	t_token	*token;

	start = sh->cmd_line_lst;
	while (sh->cmd_line_lst)
	{
		token = sh->cmd_line_lst->token_lst;
		while (token)
		{
			if (token->type == STR)
				token = tokenize_within_token(&token);
			token = token->next;
		}
		sh->cmd_line_lst = sh->cmd_line_lst->next;
	}
	sh->cmd_line_lst = start;	
}

//transformation des tokens en list chainee de commandes via le parser
void	parser(t_sh *sh)
{
	parse_tokens_in_cmd_lines(sh);//chaque commande line est separee par un pipe
	//A rajouter : fonction pour remplir cmd_line->str avant d'enlever quotes et autres
	expand_envvars_without_quotes(sh);
	//Apres avoir expand les variables d'env HORS DES QUOTES, besoin de reseparer les tokens STR avec espaces
	//export TEST="ls -la"; $TEST => doit renvoyer la commande ls, avec l'argument -la. DONC il faut retokeniser
	tokenize_after_env_exp(sh);
	process_quotes_in_cmd_lines(sh);// a voir si on met pas ca dans le lexer au lieu du parser
	update_token_type_str(sh); //remplacement du type STR par CMD, ARG, INPUTS ou OUTPUTS
	//A rajouter eventuellement : modifier les tokens CMD en token BUILTIN quand on reconnait un str correspondant a une fonction builtin
	update_elems_cmd_lines(sh);//Ajout de fdin, fdout, cmd & args dans les structures commande line

	//for each cmd line structure, print tokens, cmd, args, fdin, fdout, heredoc_mode, append_mode
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
		printf("heredoc_mode=%d, append_mode=%d\n", temp->heredoc_mode, temp->append_mode);
		printf("\n\n");
		temp = temp->next;
	}
}
