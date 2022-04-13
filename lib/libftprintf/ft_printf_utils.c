/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:23:34 by swillis           #+#    #+#             */
/*   Updated: 2022/01/31 19:09:08 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	if (c)
	{
		write(1, &c, 1);
		return (1);
	}
	else if (c == 0)
	{
		write(1, "\0", 1);
		return (1);
	}
	return (0);
}

int	ft_putstr(char *s)
{
	if (s)
	{
		write(1, s, ft_strleni(s));
		return (ft_strleni(s));
	}
	else if (s == NULL)
		return (ft_putstr("(null)"));
	return (0);
}

int	ft_finddigits_int(int n, int len_base)
{
	int				digits;
	unsigned int	nb;

	if (n == 0)
		return (1);
	digits = 0;
	if (n < 0)
	{
		nb = -n;
		digits++;
	}
	else
		nb = n;
	while (nb > 0)
	{
		nb /= len_base;
		digits++;
	}
	return (digits);
}

int	ft_strleni(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_putbase(int n, char *base)
{
	char			*str;
	unsigned int	nb;
	int				digits;
	int				i;

	digits = ft_finddigits_int(n, ft_strleni(base));
	str = malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (0);
	nb = n;
	if (n < 0)
		nb = -n;
	str[digits] = '\0';
	i = digits - 1;
	while (i >= 0)
	{
		if ((i == 0) && (n < 0))
			str[i--] = '-';
		else
			str[i--] = base[nb % ft_strleni(base)];
		nb /= ft_strleni(base);
	}
	ft_putstr(str);
	free(str);
	return (digits);
}
