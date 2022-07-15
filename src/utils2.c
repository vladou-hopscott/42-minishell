/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scottwillis <scottwillis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:51:21 by vladimir          #+#    #+#             */
/*   Updated: 2022/07/15 17:14:59 by scottwillis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_check(int fd, char *filename)
{
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(filename, 2);
		if (errno == 13)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (errno == 2)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
		{
			printf("open errno=%d\n", errno);
			ft_putstr_fd(": An error occured\n", 2);
		}
		return (1);
	}
	return (0);
}

int	ft_str_tbl_len(char **tbl)
{
	int	i;

	if (!tbl)
		return (0);
	i = 0;
	while (tbl[i])
		i++;
	return (i);
}

void	set_error_exit_status(t_sh *sh, int status)
{
	sh->exit_status = status;
	sh->error = 1;
}

//printing parsing result
//void	print_parser_result(t_sh *sh)
//{
//	t_cmd_line	*temp;
//	int	j;

//	if (sh->error == 1)
//		return ;
//	temp = sh->cmd_line_lst;
//	j = 1;
//	while (temp)
//	{
//		printf("***CMD_LINE %d ***\n", j);
//		printf("tokens : \n");
//		print_tokens(temp->token_lst);
//		printf("cmd=%s\n",temp->cmd);
//		int i = 0;
//		printf("args: [");
//		while (temp->args[i])
//		{
//			printf("%s,", temp->args[i]);
//			i++;
//		}
//		printf("]");
//		printf("\nfdout=%d, fdin=%d\n", temp->fdout, temp->fdin);
//		printf("heredoc_mode=%d, append_mode=%d\n"
//, temp->heredoc_mode, temp->append_mode);
//		printf("\n");
//		temp = temp->next;
//		j++;
//	}
//}
