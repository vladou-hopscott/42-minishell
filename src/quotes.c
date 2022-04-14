#include "minishell.h"

void	check_quote_status(t_sh *sh, char *prompt, int i)
{
	if (sh->p_quote == NO_QUOTE)
	{
		if (prompt[i] == SINGLE_QUOTE)
			sh->p_quote = SINGLE_QUOTE;
		else if (prompt[i] == DOUBLE_QUOTE)
			sh->p_quote = DOUBLE_QUOTE;
	}
	else if (sh->p_quote == SINGLE_QUOTE)
	{
		if (prompt[i] == SINGLE_QUOTE)
			sh->p_quote = NO_QUOTE;
	}
	else if (sh->p_quote == DOUBLE_QUOTE)
	{
		if (prompt[i] == DOUBLE_QUOTE)
			sh->p_quote = NO_QUOTE;
	}
}

//check if there are unclosed quotes. if so, return error status 1
int check_for_quotes(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->prompt[i])
	{
		check_quote_status(sh, sh->prompt, i);
		i++;
	}
	if (sh->p_quote != NO_QUOTE)
		return (1);
	return (0);
}




// int	manage_quotes(t_sh sh)
// {
// 	//At first, you should check if quotes are properly closed, following quoting rules: The first quote you see cancel the other type of quote until you see it again.

// 	//passage d'une 1ere fonction qui verifie si les quotes (single et double) sont bien fermees

// 	//besoin d'un statut pour le prompt ou les tokens, permettant de verifier si on est actuellement en single, double ou sans quotes

// 	//il faut utiliser ce statut lorsqu'on va tokeniser, pour savoir si on est dans un string litteral qui n'interprete pas les commandes,
// 	//ou bien si on est dans une situation ou les commandes doivent etre interpretees

// 	//ensuite important de garder en tete les comportements des double quotes avec certains caracteres

// 	return (0);
// }
