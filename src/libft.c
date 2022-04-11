/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:19:09 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/11 16:03:17 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// allocates memory for an array of n elements of size bytes each and returns
//  a pointer to the allocated memory.
void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	ptr = malloc(n * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, n * size);
	return (ptr);
}

void	ft_bzero(void *ptr, size_t n)
{
	char	*s;

	s = (char *) ptr;
	while (n > 0)
	{
		s[n - 1] = 0;
		n--;
	}
}

char	*ft_strdup(const char *s, int len)
{
	char	*dup;
	int		i;

	dup = ft_calloc(len + 1 , sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// calcule la longueur de la chaîne de caractères s,
// sans compter l'octet nul « \0 » final.
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
