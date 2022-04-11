/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:10:53 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/11 18:12:26 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// necessary libraries.
# include <stdlib.h>
# include <unistd.h>
// libraries for testing functions
# include <stdio.h>
# include <ctype.h>
# include <string.h>

// prototypes
size_t	ft_strlen(const char *s);
void	ft_bzero(void *ptr, size_t n);
void	*ft_calloc(size_t n, size_t size);
char	*ft_strdup(const char *s, int len);
char	**ft_split(char const *s, char c);

#endif
