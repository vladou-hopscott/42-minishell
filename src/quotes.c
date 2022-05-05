#include "minishell.h"

extern char	**environ;

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

// i = 0;
// while (environ && i < 3)
// {
// 	printf("%s\n", environ[i]);
// 	i++;
// }

	// var = env_findkeyvalue("USER", environ);
	// var = env_findkeyvalue("P", environ);
	// if (var)
	// 	printf("env_var=[%s]\n", var);
	// else
	// 	printf("no matching\n");


//BASH VARIABLE NAME
    // a-z, A-Z, _ and 0-9
    // May NOT begin with a number


char	*delimit_envvar(char *str)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	
	printf("env_var=\n");
	while(str[i] && str[i] != ' ') //need to be completed
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");

	return (ret);
}

char	*trim_double_quotes_in_token(t_token **token, int *i, int *j)
{
	char	*s1;
	char	*s2;
	// char	*var;

	s1 = NULL;
	s2 = NULL;
		
	s1 = ft_strndup(&(*token)->value[*j], *i - *j);
	//if NULL free tout
	
	*i = *i + 1;
	*j = *i;
	while ((*token)->value[*i] && (*token)->value[*i] != DOUBLE_QUOTE)
	{
		if ((*token)->value[*i] == '$')
		{
			delimit_envvar(&((*token)->value[*i]));
		}
		*i = *i + 1;
	}		
	if ((*token)->value[*i] == DOUBLE_QUOTE)
	{
		s2 = ft_strndup(&(*token)->value[*j], *i - *j);
		//if NULL free tout
	}
	*j = *i + 1;
	
	return (ft_strjoin_free(&s1, &s2));
}

char	*trim_single_quotes_in_token(t_token **token, int *i, int *j)
{
	char	*s1;
	char	*s2;
	
	s1 = NULL;
	s2 = NULL;
	s1 = ft_strndup(&(*token)->value[*j], *i - *j);
	//if NULL free tout
	*i = *i + 1;
	*j = *i;
	while ((*token)->value[*i] && (*token)->value[*i] != SINGLE_QUOTE)
		*i = *i + 1;
	if ((*token)->value[*i] == SINGLE_QUOTE)
	{
		s2 = ft_strndup(&(*token)->value[*j], *i - *j);
		//if NULL free tout
	}
	*j = *i + 1;	
	return (ft_strjoin_free(&s1, &s2));
}

//echo c'ou'"c"'o"u'
char	*process_quotes_in_token(t_token **token)
{
	char	*new;
	char	*temp;
	int		i;
	int		j;

	if (!str_has_quotes((*token)->value)) //if no quotes in token, skip
		return (NULL);
	i = 0;
	j = 0;
	new = NULL;
	while ((*token)->value[i])
	{
		if ((*token)->value[i] == SINGLE_QUOTE) //on entre dans des single quotes externes -> on doit les virer
		{
			temp = trim_single_quotes_in_token(token, &i, &j); 
			new = ft_strjoin_free(&new, &temp);
			//A RAJOUTER Si l'allocation de memoire echoue on arrete tout ?
		}
		else if ((*token)->value[i] == DOUBLE_QUOTE) //on entre dans des single quotes externes -> on doit les virer
		{
			temp = trim_double_quotes_in_token(token, &i, &j); 
			new = ft_strjoin_free(&new, &temp);
			//A RAJOUTER Si l'allocation de memoire echoue on arrete tout ?
		}
		i++;
	}
	//join last part of string to new
	temp = ft_strndup(&(*token)->value[j], i - j);
	return (ft_strjoin_free(&new, &temp));
}

//void	remove_quotes_in_token(t_token **a_tok)
	//faire varier le statut de token->quote : il faut supprimer au fur et a mesure les quotes inutiles
	//plusieurs manieres possibles envsageables
		//parcourir la boucle une fois avec une boucle while, et traiter au fur et a mesure. il faudrait reallouer et recreer le string au fur et a mesure qu on enleve les quotes
		//faire une fonction recursive qui enleve les quotes inutiles, jusqu a ce qu'il y en ait plus ?
