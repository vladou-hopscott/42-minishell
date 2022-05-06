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

//BASH VARIABLE NAME
    // a-z, A-Z, _ and 0-9
    // May NOT begin with a number
char	*delimit_envvar(char *str)
{
	int		i;
	char	*env_key;

	env_key = NULL;
	i = 1;
	if (ft_isdigit(str[i])) //si le 1er char est un digit, abort
		return (env_key);
	while(str[i] && (ft_isalnum(str[i]) || str[i] == '_')) //A VERIFIER si ce sont les bonnes conditions
		i++;
	env_key = ft_strndup(str + 1, i - 1);
	return (env_key);
}

char	*expand_envvar_in_token(char *str, int *i, int *j, char **s1)
{
	char	*env_key;
	char	*env_val;

	env_key = delimit_envvar(str);
	env_val = env_findkeyvalue(env_key, environ);
	if (ft_strlen(env_key) == 0)
		*i = *i + 1; //le 1er char apres le $ est faux, on le saute	
	*i = *i + ft_strlen(env_key); //on fait avancer i et j pour passer l'index apres la variable d'env
	*j = *i + 1;
	if (env_val) //si il s'agit bien d'une variable d'environnement on append sa valeur
		*s1 = ft_strjoin_free(s1, &env_val);
	ft_free_null_str(&env_key);
	return (*s1);
}

char	*trim_double_quotes_in_token(char **value, int *i, int *j)
{
	char	*s1;
	char	*s2;

	s1 = ft_strndup(&(*value)[*j], *i - *j);
	printf("A\n");
	*i = *i + 1;
	*j = *i;
	while ((*value)[*i] && (*value)[*i] != DOUBLE_QUOTE)
	{
		printf("B\n");
		if ((*value)[*i] == '$')
		{
			s2 = ft_strndup(&(*value)[*j], *i - *j); //on enregistre ce qu'il y a entre le double quote et le $
			s1 = ft_strjoin_free(&s1, &s2); //on join ca a s1
			s1 = expand_envvar_in_token(&(*value)[*j], i, j, &s1);
		}
		*i = *i + 1;
	}
	printf("C\n");
	if ((*value)[*i] == DOUBLE_QUOTE)
		s2 = ft_strndup(&(*value)[*j], *i - *j);
	*j = *i + 1;
	return (ft_strjoin_free(&s1, &s2));
}

char	*trim_single_quotes_in_token(char **value, int *i, int *j)
{
	char	*s1;
	char	*s2;
	
	s1 = NULL;
	s2 = NULL;
	s1 = ft_strndup(&(*value)[*j], *i - *j);
	*i = *i + 1;
	*j = *i;
	while ((*value)[*i] && (*value)[*i] != SINGLE_QUOTE)
		*i = *i + 1;
	if ((*value)[*i] == SINGLE_QUOTE)
		s2 = ft_strndup(&(*value)[*j], *i - *j);
	*j = *i + 1;	
	return (ft_strjoin_free(&s1, &s2));
}

//echo c'ou'"c"'o"u'
char	*process_quotes_in_token(char **value)
{
	char	*new;
	char	*temp;
	int		i;
	int		j;

	if (!str_has_quotes(*value)) //if no quotes in token, skip
		return (NULL);
	i = 0;
	j = 0;
	new = NULL;
	printf("test1\n");
	while ((*value)[i])
	{
		printf("test2\n");
		if ((*value)[i] == SINGLE_QUOTE || (*value)[i] == DOUBLE_QUOTE) //on entre dans des single ou double quotes externes -> on doit les virer
		{
			printf("test3\n");
			if ((*value)[i] == SINGLE_QUOTE)
				temp = trim_single_quotes_in_token(value, &i, &j);
			else 
				temp = trim_double_quotes_in_token(value, &i, &j);
			new = ft_strjoin_free(&new, &temp);
		}
		i++;
		printf("test3BIS\n");
	}
	printf("test4\n");
	temp = ft_strndup(&(*value)[j], i - j); 	//join last part of string to new
	return (ft_strjoin_free(&new, &temp));
}