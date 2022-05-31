#include "minishell.h"

//MODE ARGUMENTS : S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
void	open_file_fdout(t_token *token, t_cmd_line **cmd_line)
{
	if (token->type == OUTPUT)
	{
		(*cmd_line)->fdout = open(token->value,
				O_WRONLY | O_CREAT | O_TRUNC, 00644);
		(*cmd_line)->append_mode = 0;
	}
	else
	{
		(*cmd_line)->fdout = open(token->value,
				O_WRONLY | O_CREAT | O_APPEND, 00644);
		(*cmd_line)->append_mode = 1;
	}
}

int	update_fdout(t_cmd_line **cmd_line)
{
	t_token	*token;

	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == OUTPUT || token->type == OUTPUT_APPEND)
		{
			if ((*cmd_line)->fdout != 1)
				close((*cmd_line)->fdout);
			open_file_fdout(token, cmd_line);
			if ((*cmd_line)->fdout == -1)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	open_file_fdin(char *value, t_cmd_line **cmd_line)
{
	(*cmd_line)->fdin = open(value, O_RDONLY);
	if ((*cmd_line)->fdin == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

void	close_file_fdin(t_cmd_line **cmd_line)
{
	if ((*cmd_line)->fdin != 0)
		close((*cmd_line)->fdin);
	if ((*cmd_line)->heredoc_mode == 1)
	{
		(*cmd_line)->heredoc_mode = 0;
		unlink((*cmd_line)->heredoc_name);
	}
}

int	update_fdin(t_cmd_line **cmd_line)
{
	t_token	*token;
	int		error;

	error = 0;
	token = (*cmd_line)->token_lst;
	while (token)
	{
		if (token->type == INPUT || token->type == HEREDOC_LIMIT)
		{
			close_file_fdin(cmd_line);
			if (token->type == INPUT)
				error = open_file_fdin(token->value, cmd_line);
			else
				error = heredoc(token->value, cmd_line);
			if (error)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

//MODE ARGUMENT OF OPEN FUNCTION : need to check which modes have to be applied
// S_IRWXU  00700 user (file owner) has read, write, and execute permission
// S_IRUSR  00400 user has read permission
// S_IWUSR  00200 user has write permission
// S_IXUSR  00100 user has execute permission
// S_IRWXG  00070 group has read, write, and execute permission
// S_IRGRP  00040 group has read permission
// S_IWGRP  00020 group has write permission
// S_IXGRP  00010 group has execute permission
// S_IRWXO  00007 others have read, write, and execute permission
// S_IROTH  00004 others have read permission
// S_IWOTH  00002 others have write permission
// S_IXOTH  00001 others have execute permission
