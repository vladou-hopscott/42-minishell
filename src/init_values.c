/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:55:50 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/25 12:09:03 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt_values(t_sh *sh)
{
	sh->token_lst = NULL;
	sh->cmd_line_lst = NULL;
	sh->prompt = NULL;
	sh->p_index = 0;
	sh->p_quote = NO_QUOTE;
	sh->error = 0;
	sh->has_pipe = 0;
}

void	set_shlvl(t_sh *sh, int i, int lvl, char *str)
{
	char	*value;
	char	**tbl;

	i = env_findkeypos("SHLVL", sh->env);
	str = ft_strdup("SHLVL=1");
	if (i == -1)
		sh->env = tbl_append(sh->env, str);
	else
	{
		tbl = ft_split_export(sh->env[i]);
		if (tbl && tbl[1])
		{
			if (str_is_int(tbl[1]))
				lvl = ft_atoi(tbl[1]);
			if (lvl >= 9999)
				lvl = 0;
			value = ft_itoa(++lvl);
			free(str);
			str = ft_strjoin("SHLVL=", value);
			free(value);
		}
		ft_free_null_str(&sh->env[i]);
		ft_freetbl(tbl, -1);
		sh->env[i] = str;
	}
}

void	init_program_values(t_sh *sh, char **env)
{
	int		i;
	char	*str;

	ft_memset(sh, 0, sizeof(t_sh));
	init_prompt_values(sh);
	sh->exit_status = SUCCESS;
	sh->env = copy_environment(env);
	if (sh->error || sh->env == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		ft_free_values_exit(sh, FAILURE, 1);
	}
	set_shlvl(sh, 0, 0, NULL);
	i = env_findkeypos("PWD", sh->env);
	if (i == -1)
		sh->env = env_getcwd(sh->env);
	i = env_findkeypos("OLDPWD", sh->env);
	if (i == -1)
	{
		str = ft_strdup("OLDPWD");
		sh->env = tbl_append(sh->env, str);
	}
}
