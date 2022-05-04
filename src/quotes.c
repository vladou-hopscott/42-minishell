#include "minishell.h"

//besoin d'un statut pour le prompt ou les tokens, permettant de verifier si on est actuellement en single, double ou sans quotes

//il faut utiliser ce statut lorsqu'on va tokeniser, pour savoir si on est dans un string litteral qui n'interprete pas les commandes,
//ou bien si on est dans une situation ou les commandes doivent etre interpretees

//ensuite important de garder en tete les comportements des double quotes avec certains caracteres => les $

//Est-ce quon prend egalement en  compte le caractere backslash \ (echappement ?) => normalement non

//Apres avoir tokenise correctement (differences entre strings et separators), il faut supprimer les quotes inutiles des strings => les quotes qui ne sont pas interpretes en bash



//At first, you should check if quotes are properly closed, following quoting rules: The first quote you see cancel the other type of quote until you see it again.
//passage d'une 1ere fonction qui verifie si les quotes (single et double) sont bien fermees
void	check_quote_status_in_prompt(t_sh *sh, char *prompt, int i)
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

void	check_quote_status_in_token(t_token **token, int i)
{
	if ((*token)->quote == NO_QUOTE)
	{
		if ((*token)->value[i] == SINGLE_QUOTE)
			(*token)->quote = SINGLE_QUOTE;
		else if ((*token)->value[i] == DOUBLE_QUOTE)
			(*token)->quote = DOUBLE_QUOTE;
	}
	else if ((*token)->quote == SINGLE_QUOTE)
	{
		if ((*token)->value[i] == SINGLE_QUOTE)
			(*token)->quote = NO_QUOTE;
	}
	else if ((*token)->quote == DOUBLE_QUOTE)
	{
		if ((*token)->value[i] == DOUBLE_QUOTE)
			(*token)->quote = NO_QUOTE;
	}
}


//check if there are unclosed quotes. if so, return error status 1
int check_for_quotes(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->prompt && sh->prompt[i])
	{
		check_quote_status_in_prompt(sh, sh->prompt, i);
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

//suppression des quotes qui ne seront pas interpretes dans les tokens STR. Exemple : la commande ***echo "t'" oi*** renvoie ***t oi***
//il faudrait eventuellement rajouter ici l'interpretation du $ dans les double quotes egalement
//interpret_remove_quotes(sh);
//ETAPE A FAIRE APRES LE CHECK LEXICAL ET AVANT LE PASSAGE AUX CMD_LINES
void	process_quotes_in_token(t_token **token)
{
	//d'abord verifier si il y a des quotes ou double quotes presentes dans l'argument, sinon on passe
	if (!str_has_quotes((*token)->value))
		return;

	//echo c'ou'"c"'o"u'
	//traitement des quotes simples pour l'instant
	//parcourir le token. on reprend le statut quotes du token. on veut virer les quotes externes
	int i = 0;
	while ((*token)->value[i])
	{
		check_quote_status_in_token(token, i);
		i++;
	}
}

//void	remove_quotes_in_token(t_token **a_tok)
	//faire varier le statut de token->quote : il faut supprimer au fur et a mesure les quotes inutiles
	//plusieurs manieres possibles envsageables
		//parcourir la boucle une fois avec une boucle while, et traiter au fur et a mesure. il faudrait reallouer et recreer le string au fur et a mesure qu on enleve les quotes
		//faire une fonction recursive qui enleve les quotes inutiles, jusqu a ce qu'il y en ait plus ?


