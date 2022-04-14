#include "minishell.h"

char *string_token(t_sh *sh, char *prompt)
{
	char	*tmp;
	char	*str;
	int j = 0;

	while (prompt[j])
	{
		if (is_in_charset(prompt[j], CHARSET_SEP))
			break;
		j++;
	}
	tmp = ft_strndup(prompt, j);
	str = ft_strtrim(tmp, CHARSET_SPACE_TABS);
	free(tmp);
	if (j > 0)
		sh->p_index += j - 1;
	return (str);
}

// ajoute le bon token à la liste chainée des tokens sh->token_lst
//fonction a separer en plusieurs sous fonctions (tokenize string, tokenize separators...)
void	tokenizer(t_sh *sh)
{
	char	*str;

	str = NULL;
	if (sh->prompt[sh->p_index] == PIPE)
		sh->token_lst = add_back_token(sh->token_lst, PIPE, "|");
	else if (sh->prompt[sh->p_index] == RED_LEFT || sh->prompt[sh->p_index] == RED_RIGHT)
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
	else
	{
		str = string_token(sh, &sh->prompt[sh->p_index]);
		if (!str_has_only_spaces(str))
			sh->token_lst = add_back_token(sh->token_lst, STR, str);
	}
}

void lexer(t_sh *sh)
{
	//manage quotes
	//manage_quotes(sh);
	if (check_for_quotes(sh))
		return;
	printf("quote_status=%c\n", sh->p_quote);
	while (sh->prompt[sh->p_index])
	{
		tokenizer(sh);
		sh->p_index ++;
	}

	print_tokens(sh->token_lst);
	printf("list length=%d\n", list_length(sh->token_lst));
}
