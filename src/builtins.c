/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:37:07 by vnafissi          #+#    #+#             */
/*   Updated: 2022/06/28 11:21:04 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sh	g_sh;

// ======================= ECHO ====================================

void	builtin_echo(int ac, char **av, int fdout)
{
	int	i;
	int	ntrail;

	ntrail = 1;
	i = 1;
	while ((i < ac) && \
			(ft_strncmp(av[i], "-n", (ft_strlen("-n") + 1)) == 0))
	{
		ntrail = 0;
		i++;
	}
	if (i < ac)
		ft_putstr_fd(av[i++], fdout);
	while (i < ac)
	{
		ft_putchar_fd(' ', fdout);
		ft_putstr_fd(av[i++], fdout);
	}
	if (ntrail)
		ft_putchar_fd('\n', fdout);
	exit(SUCCESS);
}

// ======================= PWD ====================================

void	builtin_pwd(int ac, int fdout)
{
	char	*pwd;
	char	*buf;

	if (ac == 1)
	{
		buf = getcwd(NULL, 0);
		pwd = ft_strdup(buf);
		free(buf);
		ft_putstr_fd(pwd, fdout);
		ft_putchar_fd('\n', fdout);
		free(pwd);
		exit(SUCCESS);
	}
	else
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		exit(FAILURE);
	}
}

// ======================= CD ====================================

void	builtin_cd(int ac, char **av, char ***penv)
{
	char	*path;
	char	*newpath;

	if (ac != 2)
	{
		ft_putstr_fd("command cd only accepts relative or absolute paths\n", 2);
		set_error_exit_status(&g_sh, FAILURE);
		exit(FAILURE);
	}
	path = getcwd(NULL, 999999);
	*penv = env_export("OLDPWD", path, *penv);
	free(path);
	if (chdir(av[1]) == -1)
	{
		perror(av[1]);
		set_error_exit_status(&g_sh, FAILURE);
		exit(FAILURE);
	}
	newpath = getcwd(NULL, 999999);
	if (env_findkeypos("PWD", *penv) != -1)
		*penv = env_export("PWD", newpath, *penv);
	free(newpath);
	exit(SUCCESS);
}

// ======= OLD CD =======//

//char	*remove_trailing_slash(char *str)
//{
//	char	*new;
//	int		i;

//	i = ft_strlen(str);
//	if ((i > 0) && (str[i - 1] == '/'))
//	{
//		new = ft_strndup(str, i - 1);
//		return (new);
//	}
//	return (str);
//}

//char	*cut_root(char *path, int i)
//{
//	int		n;
//	char	*new;
//	char	**tbl;

//	if (i == 0)
//		return (path);
//	tbl = ft_split(path, '/');
//	n = 0;
//	while (tbl && tbl[n])
//		n++;
//	if (i > n)
//		return (NULL);
//	new = ft_strdup("/");
//	i = n - i;
//	n = 0;
//	while (n < i)
//	{
//		new = ft_strjoin(new, tbl[n++]);
//		new = ft_strjoin(new, "/");
//	}
//	ft_freetbl(tbl, -1);
//	free(path);
//	new = remove_trailing_slash(new);
//	return (new);
//}

// not working for relative paths . and .. and ./..
// should not accept cd without arguments
//as subject says that only relative and absolute paths are accepted.
// need to update OLDPWD in environment
// need to update sh->exit_status and sh->error
//void	builtin_cd(int ac, char **av, char ***penv)
//{
//	char	**env;
//	char	*path;
//	char	*root;
//	size_t	i;
//	int		n;

//	env = *penv;
//	if ((ac == 1) && (chdir("/") == 0))
//		*penv = env_export("PWD", "/", env);
//	else if (ac == 2)
//	{
//		path = av[1];
//		i = 0;
//		if (path[i] == '.')
//		{
//			n = 1;
//			while ((i + 1 < ft_strlen(path))
//&& (path[i + 1] == '.' || path[i + 1] == '/'))
//			{
//				if ((path[i] == '.') && (path[i + 1] == '.'))
//					n++;
//				i++;
//			}
//			root = env_findkeyvalue("PWD", env);
//			root = cut_root(root, n - 1);
//			if (root && (ft_strlen(root) > 1))
//				path = ft_strjoin(root, &path[i]);
//			else if (root)
//				path = &path[i];
//		}
//		path = remove_trailing_slash(path);
//		if ((path[0] == '/') && (chdir(path) == 0))
//			*penv = env_export("PWD", path, env);
//		else
//			ft_printf("cd: no such file or directory: %s\n", av[1]);
//	}
//	else
//		ft_printf("cd: too many arguments\n");
//}
