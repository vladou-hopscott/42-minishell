/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:15:18 by scottwillis       #+#    #+#             */
/*   Updated: 2022/07/19 21:32:00 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_numlen(int n)
{
	unsigned int	len;
	unsigned int	un;

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

char	*ft_itoa(int n)
{
	unsigned int	i;
	unsigned int	un;
	char			*str;

	i = ft_numlen(n);
	str = malloc((ft_numlen(n) + 1) * sizeof(char));
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

int	str_is_int(char *str)
{
	int		i;
	char	*ascii_num;
	int		atoi_num;
	char	*itoa_num;

	i = format_input_str(str);
	ascii_num = ft_strdup(&str[i]);
	atoi_num = ft_atoi(ascii_num);
	itoa_num = ft_itoa(atoi_num);
	if ((ft_strlen(ascii_num) == ft_strlen(itoa_num)) && \
		(ft_strncmp(ascii_num, itoa_num, ft_strlen(ascii_num)) == 0))
	{
		free(ascii_num);
		free(itoa_num);
		return (1);
	}
	free(ascii_num);
	free(itoa_num);
	return (0);
}
