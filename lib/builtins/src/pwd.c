/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:02:28 by swillis           #+#    #+#             */
/*   Updated: 2022/04/15 21:32:24 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern char	**environ;

int	main(int ac, char **av)
{
	char	*pwd;

	(void)av;
	if (ac != 1)
	{
		perror("pwd: too many arguments");
		return (-1);
	}
	pwd = env_findkeyvalue("PWD", environ);
	ft_putstr(pwd);
	ft_putchar('\n');
	free(pwd);
	return (0);
}
