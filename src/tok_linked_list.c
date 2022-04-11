/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_linked_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:59:44 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/11 12:21:30 by vnafissi         ###   ########.fr       */
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
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

void	add_back_token(t_token *list, t_token_type type, char *value)
{
	t_token *new;
	t_token	*tmp;

	new = create_token(type, value);
	if (new)
	{
		if (!list)
			list = new;
		else
		{
			tmp = list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}


/* void	ft_stack_add_front(t_stack **stack, t_stack *new)
{
	if (new)
	{
		new->next = *stack;
		*stack = new;
	}
}


int	ft_stack_len(t_stack **stack)
{
	int		i;
	t_stack	*tmp;

	if (!(*stack))
		return (0);
	tmp = *stack;
	i = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_set_null_free_elem(t_stack *elem)
{
	if (!elem)
		return ;
	elem->n = 0;
	elem->index = 0;
	elem->next = NULL;
	free(elem);
}
*/
