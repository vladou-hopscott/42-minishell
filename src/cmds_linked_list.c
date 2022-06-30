/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scottwillis <scottwillis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:16 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/30 10:35:34 by scottwillis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_cmd_line	*create_cmd_line(void)
{
	t_cmd_line	*elem;

	elem = ft_calloc(1, sizeof(t_cmd_line));
	if (!elem)
		return (NULL);
	elem->args = NULL;
	elem->cmd = NULL;
	elem->next = NULL;
	elem->str = NULL;
	elem->token_lst = NULL;
	elem->fdin = 0;
	elem->fdout = 1;
	elem->heredoc_mode = 0;
	elem->append_mode = 0;
	elem->heredoc_name = NULL;
	elem->pid = -1;
	return (elem);
}

t_cmd_line	*add_back_cmd_line(t_cmd_line *list)
{
	t_cmd_line	*new;
	t_cmd_line	*tmp;

	new = create_cmd_line();
	if (!new)
		return (NULL);
	if (!list)
		return (new);
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (list);
}
