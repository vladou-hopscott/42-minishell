#include "minishell.h"

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
}

// ======================= CD ====================================

char	*remove_trailing_slash(char *str)
{
	char	*new;
	int		i;

	i = ft_strlen(str);
	if ((i > 0) && (str[i - 1] == '/'))
	{
		new = ft_strndup(str, i - 1);
		return (new);
	}
	return (str);
}

char	*cut_root(char *path, int i)
{
	int		n;
	char	*new;
	char	**tbl;

	if (i == 0)
		return (path);
	tbl = ft_split(path, '/');
	n = 0;
	while (tbl && tbl[n])
		n++;
	if (i > n)
		return (NULL);
	new = ft_strdup("/");
	i = n - i;
	n = 0;
	while (n < i)
	{
		new = ft_strjoin(new, tbl[n++]);
		new = ft_strjoin(new, "/");
	}
	ft_freetbl(tbl, -1);
	free(path);
	new = remove_trailing_slash(new);
	return (new);
}

void	builtin_cd(int ac, char **av, char ***penv)
{
	char	**env;
	char	*path;
	char	*root;
	size_t	i;
	int		n;

	env = *penv;
	if ((ac == 1) && (chdir("/") == 0))
		*penv = env_export("PWD", "/", env);
	else if (ac == 2)
	{
		path = av[1];
		i = 0;
		if (path[i] == '.')
		{
			n = 1;
			while ((i + 1 < ft_strlen(path)) && (path[i + 1] == '.' || path[i + 1] == '/'))
			{
				if ((path[i] == '.') && (path[i + 1] == '.'))
					n++;
				i++;
			}
			root = env_findkeyvalue("PWD", env);
			root = cut_root(root, n - 1);
			if (root && (ft_strlen(root) > 1))
				path = ft_strjoin(root, &path[i]);
			else if (root)
				path = &path[i];
		}
		path = remove_trailing_slash(path);
		if ((path[0] == '/') && (chdir(path) == 0))
			*penv = env_export("PWD", path, env);
		else
			ft_printf("cd: no such file or directory: %s\n", av[1]);
	}
	else
		ft_printf("cd: too many arguments\n");
}

// ======================= PWD ====================================

void	builtin_pwd(int ac, char **env, int fdout)
{
	char	*pwd;

	if (ac == 1)
	{
		pwd = env_findkeyvalue("PWD", env);
		ft_putstr_fd(pwd, fdout);
		ft_putchar_fd('\n', fdout);
		free(pwd);
	}
	else 
		ft_printf("pwd: too many arguments\n");
}

// ======================= EXPORT ====================================

char	*str_exportvalue(char **tbl)
{
	int		i;
	char	*value;

	if (tbl[1] == NULL)
		return (NULL);
	value = ft_strdup(tbl[1]);
	i = 2;
	while (tbl && tbl[i])
	{
		value = ft_strjoin(value, tbl[i]);
		i++;
	}
	return (value);
}

void	builtin_export(int ac, char **av, char ***penv)
{
	int		i;
	char	**env;
	char	**tbl;
	char	*key;
	char	*value;

	i = 1;
	while (i < ac)
	{
		env = *penv;
		tbl = ft_split(av[i], '=');
		key = ft_strdup(tbl[0]);
		value = str_exportvalue(tbl);
		*penv = env_export(key, value, env);
		free(key);
		free(value);
		ft_freetbl(tbl, -1);
		i++;
	}
}

// ======================= UNSET ====================================

void	tbl_remove(char ***ptr, char *key)
{
	int		i;
	int		j;
	int		pos;
	char	**tbl;
	char	**new;

	tbl = *ptr;
	pos = env_findkeypos(key, tbl);
	if (pos != -1)
	{
		new = malloc(sizeof(char *) * (ft_tbllen(tbl) - 1));
		if (new)
		{
			i = 0;
			j = 0;
			while (tbl && tbl[i])
			{
				if (i == pos)
					i++;
				else
					new[j++] = ft_strdup(tbl[i++]);
			}
			new[j] = NULL;
			*ptr = new;
			ft_freetbl(tbl, -1);
		}
	}
}

void	builtin_unset(int ac, char **av, char ***penv)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		tbl_remove(penv, av[i]);
		i++;
	}
}

// ======================= ENV ====================================

void	builtin_env(int ac, char **env, int fdout)
{
	int	i;

	if (ac == 1)
	{
		i = 0;
		while (env && env[i])
		{
			ft_putstr_fd(env[i], fdout);
			ft_putchar_fd('\n', fdout);
			i++;
		}
	}
	else 
		ft_printf("env: too many arguments\n");
}

// ======================= BIN ====================================

void	cmd_pathfinder(char **pcmd, char **env)
{
	char 	*cmd;
	char	**paths;
	char	*env_path;
	char	*cmd_path;
	size_t	i;

	env_path = env_findkeyvalue("PATH", env);
	if (*pcmd && env_path)
	{
		cmd = ft_strjoin("/", (*pcmd));
		paths = ft_split(env_path, ':');
		i = 0;
		*pcmd = NULL;
		while (paths && paths[i])
		{
			cmd_path = ft_strjoin(paths[i], cmd);
			if (access(cmd_path, F_OK) == 0)
			{
				*pcmd = cmd_path;
				break ;
			}
			free(cmd_path);
			i++;
		}
		free(cmd);
		ft_freetbl(paths, -1);
	}
	free(env_path);
}

void	exec_bin(char *cmd, char **args, char **env)
{
	char	*cpy;
	int		pid;

	cpy = ft_strdup(cmd);
	cmd_pathfinder(&cmd, env);
	if (cmd)
	{
		free(args[0]);
		args[0] = ft_strdup(cmd);
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
			execve(cmd, args, env);
		waitpid(pid, NULL, 0);
		close(pid);
	}
	else
	{
		ft_printf("minishell: command not found: %s\n", cpy);
		free(cpy);
	}
}


// ======================= EXEC ====================================

int	args_to_ac(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void	executor(t_cmd_line *cmdl, char ***penv)
{
	char	**env;

	env = *penv;
	if (ft_strncmp(cmdl->cmd, "echo", ft_strlen("echo")) == 0)
		builtin_echo(args_to_ac(cmdl->args), cmdl->args, cmdl->fdout);
	else if (ft_strncmp(cmdl->cmd, "cd", ft_strlen("cd")) == 0)
		builtin_cd(args_to_ac(cmdl->args), cmdl->args, penv);
	else if (ft_strncmp(cmdl->cmd, "pwd", ft_strlen("pwd")) == 0)
		builtin_pwd(args_to_ac(cmdl->args), env, cmdl->fdout);
	else if (ft_strncmp(cmdl->cmd, "export", ft_strlen("export")) == 0)
		builtin_export(args_to_ac(cmdl->args), cmdl->args, penv);
	else if (ft_strncmp(cmdl->cmd, "unset", ft_strlen("unset")) == 0)
		builtin_unset(args_to_ac(cmdl->args), cmdl->args, penv);
	else if (ft_strncmp(cmdl->cmd, "env", ft_strlen("env")) == 0)
		builtin_env(args_to_ac(cmdl->args), env, cmdl->fdout);
	else if (ft_strncmp(cmdl->cmd, "exit", ft_strlen("exit")) == 0)
		exit(0);
	else
		exec_bin(cmdl->cmd, cmdl->args, env);
}
