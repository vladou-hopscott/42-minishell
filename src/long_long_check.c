
#include "minishell.h"

unsigned int	ft_numlen_ll(long long n)
{
	unsigned long long	len;
	unsigned long long	un;

	len = 0;
	if (n < 0)
	{
		len++;
		un = -n;
	}
	else
		un = n;
	if (un == 0)
		len++;
	while (un > 0)
	{
		len++;
		un /= 10;
	}
	return (len);
}

char	*ft_lltoa(long long n)
{
	unsigned long long	i;
	unsigned long long	un;
	char			    *str;

	i = ft_numlen_ll(n);
	str = malloc((ft_numlen_ll(n) + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		un = -n;
	}
	else
		un = n;
	str[i--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (un > 0)
	{
		str[i--] = '0' + un % 10;
		un /= 10;
	}
	return (str);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r')
		return (1);
	if (c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

static int	format_input_str(char *str)
{
	int		i;
	int		sign;

	i = 0;
	sign = +1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		str[i] = '+';
		if (sign < 0)
			str[i] = '-';
		i++;
	}
	if (sign < 0)
		i -= 1;
	return (i);
}

int	str_is_long_long(char *str)
{
	int		    i;
	char	    *ascii_num;
	long long	atoll_num;
	char	    *lltoa_num;

	i = format_input_str(str);
	ascii_num = ft_strdup(&str[i]);
	atoll_num = ft_atoll(ascii_num);
	lltoa_num = ft_lltoa(atoll_num);
	if ((ft_strlen(ascii_num) == ft_strlen(lltoa_num)) && \
		(ft_strncmp(ascii_num, lltoa_num, ft_strlen(ascii_num)) == 0))
	{
		free(ascii_num);
		free(lltoa_num);
		return (1);
	}
	free(ascii_num);
	free(lltoa_num);
	return (0);
}
