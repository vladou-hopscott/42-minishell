#include "minishell.h"

char *process_string_token(t_sh *sh, char *prompt)
{
	char	*tmp;
	char	*str;
	int		j = 0;

	while (prompt[j])
	{
		if (is_in_charset(prompt[j], CHARSET_SEP) && sh->p_quote == NO_QUOTE)
			break;
		j++;
		check_quote_status_in_prompt(sh, prompt, j);
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
	if (sh->prompt[sh->p_index] == RED_INPUT && sh->prompt[sh->p_index + 1] == RED_INPUT)
	{
		sh->token_lst = add_back_token(sh->token_lst, HEREDOC, "<<");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == RED_OUTPUT && sh->prompt[sh->p_index + 1] == RED_OUTPUT)
	{
		sh->token_lst = add_back_token(sh->token_lst, RED_APPEND, ">>");
		sh->p_index++;
	}
	else if (sh->prompt[sh->p_index] == RED_INPUT)
		sh->token_lst = add_back_token(sh->token_lst, RED_INPUT, "<");
	else if (sh->prompt[sh->p_index] == RED_OUTPUT)
		sh->token_lst = add_back_token(sh->token_lst, RED_OUTPUT, ">");
}

// ajoute le bon token à la liste chainée des tokens sh->token_lst
//fonction a separer en plusieurs sous fonctions (tokenize string, tokenize separators...)
void	tokenizer(t_sh *sh)
{
	char	*str;

	str = NULL;

	//A chaque debut on verifie si on entre ou sort de quotes
	check_quote_status_in_prompt(sh, sh->prompt, sh->p_index);

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

	//tokeniser (traitement du prompt pour en sortir une liste chainee avec maillon = string ou separateur) en tenant compte des single et double quotes;
	while (sh->prompt[sh->p_index])
	{
		tokenizer(sh);
		sh->p_index ++;
	}

	//A partir de cette 1ere liste de tokens, verification des erreurs de syntaxe des redirections (exemples : > >, >|, ||, etc...)
	//fonction a coder qui liste toutes les erreurs de syntaxe liees aux redirections : check_syntax_error();
}
