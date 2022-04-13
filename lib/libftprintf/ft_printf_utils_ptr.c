/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_ptr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:23:34 by swillis           #+#    #+#             */
/*   Updated: 2022/01/31 19:09:09 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_finddigits_ull(unsigned long long add, int len_base)
{
	int	digits;

	if (add == 0)
		return (1);
	digits = 0;
	while (add > 0)
	{
		add /= (unsigned long long)len_base;
		digits++;
	}
	return (digits);
}

int	ft_putptr(unsigned long long add, char *base)
{
	char	*str;
	int		i;
	int		digits;
	int		lenbase;

	lenbase = ft_strleni(base);
	digits = ft_finddigits_ull(add, lenbase);
	str = malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (0);
	str[digits] = '\0';
	i = digits - 1;
	while (i >= 0)
	{
		str[i] = base[add % (unsigned long long)lenbase];
		add /= (unsigned long long)lenbase;
		i--;
	}
	ft_putstr("0x");
	ft_putstr(str);
	free(str);
	return (2 + digits);
}
