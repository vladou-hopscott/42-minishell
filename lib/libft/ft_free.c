#include "libft.h"

void	ft_free_null_str(char **str)
{
	if (*str)
	{
		printf("%s\n", *str);
		free(*str);
		*str = NULL;
	}
}
