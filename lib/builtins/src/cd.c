/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:45:16 by vladimir          #+#    #+#             */
/*   Updated: 2022/06/13 17:27:09 by vladimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern  char	**environ;

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	write(fd, s, len);
}

int	main(int ac, char **av)
{
	char    *path;
    char    *newpath;
    char    *pwd;
    
    if (ac != 2)
    {
        ft_putstr_fd("command cd requires exactly 1 argument\n", 2);
        return (1);
    }
	path = av[1];    
    if (chdir(path) == -1)
    {
        perror(path);
        //TO ADD : need to set sh->exit_status = 2
        //TO ADD : need to set sh->error = 1
        return (1);
    }
    newpath = getcwd(NULL, 999999);
    environ = env_export("PWD", newpath, environ);
    pwd = env_findkeyvalue("PWD", environ);
    printf("current working directory and pwd successfuly set to :%s\n", pwd);
    free(newpath);
    return (0);
}
