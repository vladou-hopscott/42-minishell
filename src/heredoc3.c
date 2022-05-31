#include "minishell.h"

static	char	*choose_filename(void)
{
	char	*filename;
	int		file_exists;
	int		i;
	char	*nbr;

	i = 1;
	filename = ft_strdup("./heredoc");
	file_exists = open(filename, O_RDONLY);
	while (file_exists != -1)
	{
		close(file_exists);
		nbr = ft_itoa(i);
		filename = ft_strjoin_free(&filename, &nbr);
		file_exists = open(filename, O_RDONLY);
		i++;
	}
	close(file_exists);
	return (filename);
}

//MODE ARGUMENTS : S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
int	initialize_heredoc(t_cmd_line **cmd_line)
{
	(*cmd_line)->heredoc_name = choose_filename();
	(*cmd_line)->heredoc_mode = 1;
	(*cmd_line)->fdin = open((*cmd_line)->heredoc_name,
			O_RDWR | O_CREAT | O_APPEND, 00644);
	if ((*cmd_line)->fdin == -1)
		return (1);
	return (0);
}
