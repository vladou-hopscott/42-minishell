/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:02:35 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/13 16:13:10 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Écrit la chaine de caractères ’s’ sur le file
//descriptor donné.

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
