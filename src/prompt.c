#include "minishell.h"
#include "parsing.h"

void listen_prompt(t_sh *sh)
{
	sh->prompt = readline("➜ minishell ");
	add_history(sh->prompt); //verifier si il y a d'autres choses a ajouter pour securiser ou stocker l'historique
}
