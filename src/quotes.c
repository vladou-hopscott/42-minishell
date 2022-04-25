#include "minishell.h"

//besoin d'un statut pour le prompt ou les tokens, permettant de verifier si on est actuellement en single, double ou sans quotes

//il faut utiliser ce statut lorsqu'on va tokeniser, pour savoir si on est dans un string litteral qui n'interprete pas les commandes,
//ou bien si on est dans une situation ou les commandes doivent etre interpretees

//ensuite important de garder en tete les comportements des double quotes avec certains caracteres => les $

//Est-ce quon prend egalement en  compte le caractere backslash \ (echappement ?) => normalement non

//Apres avoir tokenise correctement (differences entre strings et separators), il faut supprimer les quotes inutiles des strings => les quotes qui ne sont pas interpretes en bash



//At first, you should check if quotes are properly closed, following quoting rules: The first quote you see cancel the other type of quote until you see it again.
//passage d'une 1ere fonction qui verifie si les quotes (single et double) sont bien fermees
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
	while (sh->prompt && sh->prompt[i])
	{
		check_quote_status(sh, sh->prompt, i);
		i++;
	}
	if (sh->p_quote != NO_QUOTE)
		return (1);
	return (0);
}

int	str_has_quotes(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (is_in_charset(str[i], "\'\""))
			return (1);
		i++;
	}
	return (0);
}

void	remove_quotes_in_token(t_token **a_tok)
{
	int	i;

	//d'abord verifier si il y a des quotes ou double quotes presentes dans l'argument, sinon on passe
	if (!str_has_quotes((*a_tok)->value))
		return;


	//parcourir le token STR
	i = 0;
	while ((*a_tok)->value[i])
	{
		if (1)
		{
			i = 1;
		}

		i++;
	}

	//traitement des simple quotes : il suffit de considerer tout

	//faire varier le statut de token->quote : il faut supprimer au fur et a mesure les quotes inutiles
	//plusieurs manieres possibles envsageables
		//parcourir la boucle une fois avec une boucle while, et traiter au fur et a mesure. il faudrait reallouer et recreer le string au fur et a mesure qu on enleve les quotes
		//faire une fonction recursive qui enleve les quotes inutiles, jusqu a ce qu'il y en ait plus ?

}

void	interpret_remove_quotes(t_sh *sh)
{
	t_token	*tmp;

	tmp = sh->token_lst;
	while (tmp->next)
	{
		if (tmp->type == STR)
			remove_quotes_in_token(&tmp);
		tmp = tmp->next;
	}
}
