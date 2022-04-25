#include "minishell.h"

char *process_string_token(t_sh *sh, char *prompt)
{
	char	*tmp;
	char	*str;
	int		j = 0;

	while (prompt[j])
	{
		//printf("i=%d, status=%c\n", j, sh->p_quote);
		if (is_in_charset(prompt[j], CHARSET_SEP) && sh->p_quote == NO_QUOTE)
			break;
		j++;
		check_quote_status(sh, prompt, j);
	}
	tmp = ft_strndup(prompt, j);
	str = ft_strtrim(tmp, CHARSET_SPACE_TABS);
	free(tmp);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}

void	process_redirect_token(t_sh *sh)
{
	if (sh->prompt[sh->p_index] == RED_LEFT && sh->prompt[sh->p_index + 1] == RED_LEFT)
	{
		sh->token_lst = add_back_token(sh->token_lst, DOUBLE_RED_LEFT, "<<");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == RED_RIGHT && sh->prompt[sh->p_index + 1] == RED_RIGHT)
	{
		sh->token_lst = add_back_token(sh->token_lst, DOUBLE_RED_RIGHT, ">>");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == RED_LEFT)
		sh->token_lst = add_back_token(sh->token_lst, RED_LEFT, "<");
	else if (sh->prompt[sh->p_index] == RED_RIGHT)
		sh->token_lst = add_back_token(sh->token_lst, RED_RIGHT, ">");
}

// ajoute le bon token à la liste chainée des tokens sh->token_lst
//fonction a separer en plusieurs sous fonctions (tokenize string, tokenize separators...)
void	tokenizer(t_sh *sh)
{
	char	*str;

	str = NULL;

	//A chaque debut on verifie si on entre ou sort de quotes
	check_quote_status(sh, sh->prompt, sh->p_index);

	//printf("sh->p_index=%d, status=%c\n", sh->p_index, sh->p_quote);
	if (sh->p_quote == NO_QUOTE && is_in_charset(sh->prompt[sh->p_index], CHARSET_SEP))
	{
		if (sh->prompt[sh->p_index] == PIPE)
			sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
		else
			process_redirect_token(sh);
	}
	else
	{
		str = process_string_token(sh, &sh->prompt[sh->p_index]);
		if (!str_has_only_spaces(str))
			sh->token_lst = add_back_token(sh->token_lst, STR, str);
	}
}

void lexer(t_sh *sh)
{
	//verifier qu'il n'y a pas de quotes ouvertes
	if (check_for_quotes(sh))
	{
		printf("ERROR : unclosed quotes\n");
		return; //voir quel message d'erreur et comment traiter l'erreur
	}

	//tokeniser (separation entre strings et separateurs, stockage dans une liste chainee) en tenant compte des single et double quotes;
	while (sh->prompt[sh->p_index])
	{
		tokenizer(sh);
		sh->p_index ++;
	}

	//suppression des quotes qui ne seront pas interpretes dans les tokens STR. Exemple : la commande ***echo "t'" oi*** renvoie ***t oi***
	//il faudrait eventuellement rajouter ici l'interpretation du $ dans les double quotes egalement
	//interpret_remove_quotes(sh);

	print_tokens(sh->token_lst);
	printf("list length=%d\n", list_length(sh->token_lst));
}
