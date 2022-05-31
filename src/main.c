#include "minishell.h"

//printing parsing result
void	print_parser_result(t_sh *sh)
{
	t_cmd_line *temp;
	int j;

	if (sh->error == 1)
		return;
	temp = sh->cmd_line_lst;
	j = 1;
	while (temp)
	{
		printf("***CMD_LINE %d ***\n", j);
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
		printf("heredoc_mode=%d, append_mode=%d\n"	, temp->heredoc_mode, temp->append_mode);
		printf("\n");
		temp = temp->next;
		j++;
	}
}

int	main(void)
{
	t_sh	sh;
	//t_token	*token;

	handle_signals();
	init_values(&sh);
	sh.env = init_environment();
	while (1)
	{
		listen_prompt(&sh); //générer un prompt avec readline() et enregistrer la commande tapée
		lexer(&sh); //analyse lexicale de la commande et verif erreurs de syntaxe des redirections
		parser(&sh); //traitement des tokens en cmd lines, separees par des pipes. chaque cmd line represente un processus
		if (sh.error)
		{
			free_values(&sh, 0);
			init_values(&sh);
			continue ;
		}
		print_parser_result(&sh);

		//token = sh.token_lst;
		// while (token)
		// {
		// 	sh.env = executor(token, sh.env);
		// 	token = token->next;
		// }
		free_values(&sh, 0);
		init_values(&sh);
	}
	free_values(&sh, 1);
	if (sh.error == 1)
		return (1);
	return (0);
}
