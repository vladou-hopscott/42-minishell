#include "minishell.h"

t_sh	sh;

void	check_program_args(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		exit(FAILURE);
	}
}

void	execute_cmds(t_sh *sh)
{
	t_cmd_line	*cmdl;

	cmdl = sh->cmd_line_lst;
	while (cmdl)
	{
		executor(cmdl, &sh->env);
		cmdl = cmdl->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	check_program_args(argc);
	handle_signals();
	init_program_values(&sh, env);
	while (1)
	{
		listen_prompt(&sh);
		lexer(&sh);
		parser(&sh);
		if (sh.error)
		{
			free_values(&sh, 0);
			init_prompt_values(&sh);
			continue ;
		}
		// print_parser_result(&sh);
		execute_cmds(&sh);
		free_values(&sh, 0);
		if (!sh.error)
			sh.exit_status = SUCCESS;
		init_prompt_values(&sh);
	}
	free_values(&sh, 1);
	if (sh.error == 1)
		return (1);
	return (0);
}
