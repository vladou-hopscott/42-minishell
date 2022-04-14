
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
// char	**ft_split(char const *s, char c);
int		is_in_charset(char c, const char *charset);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);

#endif
