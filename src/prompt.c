
#include "minishell.h"

//The line returned is allocated with malloc(3);
//the caller must free it when finished.
void listen_prompt(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	if (!sh->prompt)
	{
		sh->error = 1;
		pgm_error(sh);
	}
	add_history(sh->prompt); //verifier si il y a d'autres choses a ajouter pour securiser ou stocker l'historique
}
