/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:28:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 19:21:52 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*elem;

	elem = ft_calloc(1, sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->type = type;
	elem->value = ft_strdup(value);
	elem->next = NULL;
	elem->quote = NO_QUOTE;
	elem->tk_is_empty_doll = 0;
	return (elem);
}

t_token	*add_back_token(t_token *list, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = create_token(type, value);
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

t_token	*add_middle_token(t_token *current, t_token_type type, char *value)
{
	t_token	*new;

	new = create_token(type, value);
	if (!new)
		return (NULL);
	if (!current)
		return (new);
	else
	{
		new->next = current->next;
		current->next = new;
	}
	return (new);
}

int	count_arg_tokens(t_token *li)
{
	int	size;

	size = 0;
	while (li != NULL)
	{
		if (li->type == ARG || li->type == CMD)
			size++;
		li = li->next;
	}
	return (size);
}
