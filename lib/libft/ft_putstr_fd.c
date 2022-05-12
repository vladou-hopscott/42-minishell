/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:02:35 by vnafissi          #+#    #+#             */
/*   Updated: 2022/05/12 18:02:36 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Écrit la chaine de caractères ’s’ sur le file
//descriptor donné.

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	write(fd, s, len);
}
