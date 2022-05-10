#include "minishell.h"

extern char	**environ;

char	*expand_envvar(char *str, int *i, int *j, char **s1)
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

char	*expand_envvars_in_token(char **value)
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;
	int		quote_status;

	if (!str_has_dollar_without_quotes(*value)) //if no dollars without quotes in token, skip
		return (NULL);
	i = 0;
	j = 0;
	s1 = NULL;
	quote_status = NO_QUOTE;
	while ((*value)[i])
	{
		quote_status = check_quote_status_in_str((*value)[i], quote_status);
		if (quote_status == NO_QUOTE && (*value)[i] == '$')
		{
			s2 = ft_strndup(&(*value)[j], i - j); //on enregistre ce qu'il y a avant le $
			s1 = ft_strjoin_free(&s1, &s2); //on join ca a s1
			s1 = expand_envvar(&(*value)[i], &i, &j, &s1);
		}
		i++;
	}
	s2 = ft_strndup(&(*value)[j], i - j); 	//join last part of string to new
	return (ft_strjoin_free(&s1, &s2));	
}
