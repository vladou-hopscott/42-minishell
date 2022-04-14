/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:10:53 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/14 14:11:07 by swillis          ###   ########.fr       */
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
char	*ft_strndup(const char *s, int len);

char	**ft_split(char *s, char c);

int		ft_atoi(char *nptr);
char	*ft_strdup(char *s);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
