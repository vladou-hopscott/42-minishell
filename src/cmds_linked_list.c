#include "minishell.h"
#include "parsing.h"

t_cmd_line	*create_cmd_line()
{
	t_cmd_line	*elem;

	elem = ft_calloc(1, sizeof(t_cmd_line));
	if (!elem)
		return (NULL);
	return (elem);
}

t_cmd_line	*add_back_cmd_line(t_cmd_line *list)
{
	t_cmd_line *new;
	t_cmd_line	*tmp;

	new = create_cmd_line();
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
