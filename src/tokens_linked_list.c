/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:28:42 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/31 21:32:59 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

void	print_tokens(t_token *li)
{
	while (li != NULL)
	{
		printf("[%s]", li->value);
		li = li->next;
	}
	printf("\n");
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

//void	ft_set_null_free_elem(t_token *elem)
//{
//	if (!elem)
//		return ;
//	elem->value = NULL;
//	elem->next = NULL;
//	free(elem);
//}

//void	ft_set_null_free_list(t_token **a_list)
//{
//	t_token	*tmp;

//	if (!(*a_list))
//		return ;
//	while (*a_list)
//	{
//		tmp = (*a_list)->next;
//		ft_set_null_free_elem(*a_list);
//		*a_list = tmp;
//	}
//}
