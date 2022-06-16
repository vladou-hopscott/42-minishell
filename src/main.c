#include "minishell.h"

t_sh	sh;

//printing parsing result
void	print_parser_result(t_sh *sh)
{
	t_cmd_line *temp;
	int j;

	if (sh->error == 1)
		return;
	temp = sh->cmd_line_lst;
	j = 1;
	while (temp)
	{
		printf("***CMD_LINE %d ***\n", j);
		printf("tokens : \n");
		print_tokens(temp->token_lst);
		printf("cmd=%s\n",temp->cmd);
		int i = 0;
		printf("args: [");
		while (temp->args[i])
		{
			printf("%s,", temp->args[i]);
			i++;
		}
		printf("]");
		printf("\nfdout=%d, fdin=%d\n", temp->fdout, temp->fdin);
		printf("heredoc_mode=%d, append_mode=%d\n"	, temp->heredoc_mode, temp->append_mode);
		printf("\n");
		temp = temp->next;
		j++;
	}
}

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

	// int i = 0;
	// while (sh.env[i])
	// {
	// 	printf("%s\n", sh.env[i]);
	// 	i++;
	// }
	
	while (1)
	{
		listen_prompt(&sh); //générer un prompt avec readline() et enregistrer la commande tapée
		lexer(&sh); //analyse lexicale de la commande et verif erreurs de syntaxe des redirections
		parser(&sh); //traitement des tokens en cmd lines, separees par des pipes. chaque cmd line represente un processus
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
