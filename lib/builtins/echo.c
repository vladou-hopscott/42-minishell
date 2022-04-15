#include <unistd.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while(str && str[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	main(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		ft_putstr(av[i]);
		if (i < ac - 1)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}
