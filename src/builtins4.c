/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:07:49 by vladimir          #+#    #+#             */
/*   Updated: 2022/07/23 19:43:31 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= UNSET ====================================

int	unset_is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (key == NULL)
		return (SUCCESS);
	if (key[i] == '\0')
		return (SUCCESS);
	if (key[i] != '_' && !ft_isalpha(key[i]))
		return (FAILURE);
	i = 1;
	while (key && key[i])
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	tbl_remove(char ***ptr, char *key)
{
	int		i;
	int		j;
	int		pos;
	char	**tbl;
	char	**new;

	tbl = *ptr;
	pos = env_findkeypos(key, tbl);
	if (pos == -1)
		return ;
	new = malloc(sizeof(char *) * (ft_tbllen(tbl) - 1));
	if (!new)
		return ;
	i = 0;
	j = 0;
	while (tbl && tbl[i])
	{
		if (i == pos)
			i++;
		else
			new[j++] = ft_strdup(tbl[i++]);
	}
	new[j] = NULL;
	*ptr = new;
	ft_freetbl(tbl, -1);
}

void	builtin_unset(int ac, char **av, char ***penv)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (unset_is_valid_key(av[i]) == FAILURE)
		{
			err_unset_invalid(&g_sh, av[i]);
			return ;
		}
		if (!g_sh.has_pipe)
			tbl_remove(penv, av[i]);
		i++;
	}
	if (g_sh.has_pipe)
		ft_free_values_exit(&g_sh, SUCCESS, 1);
}
