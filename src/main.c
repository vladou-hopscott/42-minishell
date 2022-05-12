
#include "minishell.h"

int	main(void)
{
	t_sh	sh;
	//t_token	*token;

	init_values(&sh);
	sh.env = init_environment();
	while (1)
	{
		listen_prompt(&sh); //générer un prompt avec readline() et enregistrer la commande tapée
		lexer(&sh); //analyse lexicale de la commande et verif erreurs de syntaxe des redirections
		parser(&sh); //traitement des tokens en cmd lines, separees par des pipes. chaque cmd line represente un processus
		//token = sh.token_lst;
		// while (token)
		// {
		// 	sh.env = executor(token, sh.env);
		// 	token = token->next;
		// }
		printf("END\n");
		free_values(&sh, 0);
		init_values(&sh);
	}
	free_values(&sh, 1);
	if (sh.error == 1)
		return (1);
	return (0);
}
