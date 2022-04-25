
#include "minishell.h"

int	main(void)
{
	//Faut-il déclarer sh comme une variable globale (pour garder en mémoire les commandes successives ?)
	t_sh	sh;
	t_token	*token;

	init_values(&sh);
	sh.env = init_environment();
	printf("env0=%s, env1=%s, env2=%s\n\n", sh.env[0], sh.env[1], sh.env[2]);
	while (1)
	{
		listen_prompt(&sh); //générer un prompt avec readline() et enregistrer la commande tapée
		lexer(&sh); //analyse lexicale de la commande

		token = sh.token_lst;
		// while (token)
		// {
		// 	sh.env = executor(token, sh.env);
		// 	token = token->next;
		// }

		init_values(&sh);
	}

	//penser à free tout ce qui a été initialisé avec readline
	free_values(&sh);

	return (0);
}
