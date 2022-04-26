#include "minishell.h"

//1) apres avoir utilise le lexer une pre;iere fois, on le reutilise pour separation avec les pipes en command lines

void	parser(t_sh *s)
{
	//1) creation du 1er maillon cmd_line
	//2) tant qu on ne tombe pas sur un pipe, on stock tous les tokens dans la 1ere command line
	//3) quand on tombe sur un pipe, on cree un 2nd maillon cmd_line, et on y fourre tous les tokens suivants jusqu'au prochain pipe

	//4)gestion des quotes et des variables d'environnement : voir en dessous

}

//suppression des quotes qui ne seront pas interpretes dans les tokens STR. Exemple : la commande ***echo "t'" oi*** renvoie ***t oi***
//il faudrait eventuellement rajouter ici l'interpretation du $ dans les double quotes egalement
//interpret_remove_quotes(sh);

