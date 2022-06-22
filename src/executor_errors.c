#include "minishell.h"

void	err_cmd_not_found(t_sh *sh, char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	sh->error = 1;
	sh->exit_status = CMD_NOT_FOUND;
}
