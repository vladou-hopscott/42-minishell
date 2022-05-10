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
	elem->quote = NO_QUOTE;
	return (elem);
}

t_token	*add_back_token(t_token *list, t_token_type type, char *value)
{
	t_token *new;
	t_token	*tmp;

	new = create_token(type, value);
	if (!new)
		return NULL;

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
	t_token *new;

	new = create_token(type, value);
	if (!new)
		return NULL;
	if (!current)
		return (new);
	else
	{
		new->next = current->next;
		current->next = new;
	}
	return (current);
}


void print_tokens(t_token *li)
{
	while(li != NULL)
	{
		printf("[%s] type=%u, ", li->value, li->type);
		li = li->next;
	}
	printf("\n");
}


int count_arg_tokens(t_token *li)
{
	int size = 0;

	while(li != NULL)
	{
		if (li->type == ARG)
			size++;
		li = li->next;
	}
	return size;
}

int list_length(t_token *li)
{
	int size = 0;

	while(li != NULL)
	{
		size++;
		li = li->next;
	}
	return size;
}

void	ft_set_null_free_elem(t_token *elem)
{
	if (!elem)
		return ;
	elem->value = NULL;
	elem->next = NULL;
	free(elem);
}

void	ft_set_null_free_list(t_token **a_list)
{
	t_token	*tmp;

	if (!(*a_list))
		return ;
	while (*a_list)
	{
		tmp = (*a_list)->next;
		ft_set_null_free_elem(*a_list);
		*a_list = tmp;
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
