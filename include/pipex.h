/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:47:18 by swillis           #+#    #+#             */
/*   Updated: 2022/04/14 14:06:18 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

//********************** STRUCTURES **********************//

typedef struct s_pvars {
	int			fd[2];
	int			file1;
	int			file2;
	int			pid1;
	int			pid2;
	char		*cmd1;
	char		*cmd2;
	char		**args1;
	char		**args2;
	char		*env_path;
	char		*path1;
	char		*path2;
}				t_pvars;

//********************** LIBFT **********************//
size_t	ft_strlen(const char *str);
char	**ft_freetbl(char **tbl, int pos);
// char	**ft_split(char *s, char c);
// char	*ft_strdup(const char *src);
// char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *str, const char *find, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//********************** UTILS **********************//
int		close_fds(int file1, int file2);
char	*env_pathfinder(char **env);
char	*cmd_pathfinder(char *cmd, char *env_path);
char	*cmd_strfinder(char *str);
char	**cmd_argstbl(char *str, char *path);

//********************** MAIN **********************//
int		close_fds(int file1, int file2);
char	*env_pathfinder(char **env);
char	*cmd_pathfinder(char *cmd, char *env_path);
char	*cmd_strfinder(char *str);
char	**cmd_argstbl(char *str, char *path);

#endif
