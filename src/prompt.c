
#include "minishell.h"

//The line returned is allocated with malloc(3);
//the caller must free it when finished.
void listen_prompt(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	if (!sh->prompt)
	{
		sh->error = 1;
		ft_putstr_fd("exit\n", 1);
		exit(0); //a voir comment on gere les codes exit
	}
	add_history(sh->prompt); //verifier si il y a d'autres choses a ajouter pour securiser ou stocker l'historique
}
