/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:23:34 by swillis           #+#    #+#             */
/*   Updated: 2022/01/31 19:09:05 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_finddigits_unsign(unsigned int n, int len_base)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		n /= (unsigned int)len_base;
		digits++;
	}
	return (digits);
}

int	ft_putbase_unsign(unsigned int n, char *base)
{
	char	*str;
	int		i;
	int		digits;
	int		lenbase;

	lenbase = ft_strleni(base);
	digits = ft_finddigits_unsign(n, lenbase);
	str = malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (0);
	str[digits] = '\0';
	i = digits - 1;
	while (i >= 0)
	{
		str[i] = base[n % (unsigned int)lenbase];
		n /= (unsigned int)lenbase;
		i--;
	}
	ft_putstr(str);
	free(str);
	return (digits);
}
