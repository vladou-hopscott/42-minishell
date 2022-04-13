/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:50:12 by swillis           #+#    #+#             */
/*   Updated: 2022/01/31 19:09:08 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_putvar(const char c, va_list vars);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putbase(int n, char *base);
int	ft_putptr(unsigned long long add, char *base);
int	ft_putbase_unsign(unsigned int n, char *base);
int	ft_varcheck(const char *str);
int	ft_finddigits_int(int n, int len_base);
int	ft_finddigits_ull(unsigned long long add, int len_base);
int	ft_finddigits_unsign(unsigned int n, int len_base);
int	ft_strleni(char *str);
int	ft_printf(const char *str, ...);

#endif
