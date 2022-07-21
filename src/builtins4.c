/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:07:49 by vladimir          #+#    #+#             */
/*   Updated: 2022/07/21 18:06:40 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= UNSET ====================================

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
	if (!g_sh.has_pipe)
	{
		while (i < ac)
		{
			tbl_remove(penv, av[i]);
			i++;
		}
	}
	if (g_sh.has_pipe)
		exit(SUCCESS);
}
