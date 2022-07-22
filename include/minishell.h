/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:17:57 by swillis           #+#    #+#             */
/*   Updated: 2022/07/22 11:27:41 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"
# include "ft_printf.h"
# include "parsing.h"
# include "env_manager.h"

//********************** EXIT STATUS **********************//

typedef enum s_exit_status
{
	SUCCESS = 0,
	FAILURE = 1,
	MAJOR_FAILURE = 2,
	CMD_NOT_FOUND = 127,
	PGM_ABORTED = 132,
	INVALID_EXIT = 255
}	t_exit_status;

//*************** STRUCTURE PRINCIPALE ***************//
typedef struct s_sh
{
	char			**env;
	t_token			*token_lst;
	t_cmd_line		*cmd_line_lst;
	t_exit_status	exit_status;
	char			*prompt;
	int				p_index;
	int				p_quote;
	int				error;
	int				has_pipe;
}	t_sh;

//********************** FUNCTIONS **********************//

//********** INITIALIZATION **********//
void		init_program_values(t_sh *sh, char **env);
void		init_prompt_values(t_sh *sh);
void		free_values(t_sh *sh, int free_env);

//********** PROMPT **********//
void		listen_prompt(t_sh *sh);

//********** LEXER **********//
void		lexer(t_sh *sh);
void		tokenizer(t_sh *sh);
char		*process_string_token(t_sh *sh, char *prompt);
void		process_redirect_token(t_sh *sh);
void		update_token_type_str(t_sh *sh);
void		check_syntax_errors(t_sh *sh);
int			is_redirection(t_token_type type);
int			error_next_is_pipe(t_token *token);
int			error_first_is_pipe(int i);

//********** PARSER **********//
void		parser(t_sh *s);
t_cmd_line	*add_back_cmd_line(t_cmd_line *list);
t_cmd_line	*create_cmd_line(void);
void		update_elems_cmd_lines(t_sh *sh);
int			update_cmd(t_cmd_line **cmd_line);
int			update_args(t_cmd_line **cmd_line);
int			count_arg_tokens(t_token *li);
void		process_quotes_in_tokens(t_cmd_line **cmd_line);
char		*process_quotes_in_token(char **value);
void		expand_envvars_in_tokens(t_cmd_line **cmd_line);
char		*expand_envvars_in_token(char **value);
char		*expand_envvar(char *str, t_idx *idx, char **s1, t_quote qs);
char		*delimit_envvar(char *str);
t_token		*tokenize_within_token(t_token **token);
t_token		*create_tokens_within_tokens(t_token **token, char *str);
void		update_token_type_heredoc_limit(t_sh *sh);
void		update_tokens_hd_limit(t_cmd_line **cmd_line);
void		print_parser_result(t_sh *sh);

//********** REDIRECTIONS **********//
void		close_file_fdin(t_cmd_line **cmd_line);
int			open_file_fdin(char *filename, t_cmd_line **cmd_line);
int			update_fdin_fdout(t_cmd_line **cmd_line);
int			update_fdin(t_cmd_line **cmd_line, t_token *token);
int			update_fdout(t_cmd_line **cmd_line, t_token *token);

//********** SIGNALS **********//
void		handle_signals(int activate_sigquit);
void		heredoc_handler(int sigtype);

//********** QUOTES **********//
int			check_for_quotes(t_sh *sh);
int			check_quote_status_in_str(char c, int quote_status);
void		interpret_remove_quotes(t_sh *sh);

//********** LINKED LIST TOKENS **********//
t_token		*create_token(t_token_type type, char *value);
t_token		*add_back_token(t_token *list, t_token_type type, char *value);
void		print_tokens(t_token *li);
void		ft_set_null_free_list(t_token **a_list);
t_token		*add_middle_token(t_token *current, t_token_type type, char *value);

//********** HERE DOCUMENTS **********//
int			heredoc(char *delimitor, t_cmd_line **cmd_line);
int			initialize_heredoc(t_cmd_line **cmd_line);
int			run_children(char *delimitor);
char		*read_heredoc_line(t_cmd_line **cmd_line,
				int quotes, char *delimitor);
char		*expand_heredoc_line(char **str);
void		write_heredoc_line(char **tmp, t_cmd_line **cmd_line, int i);
char		*trim_quotes_in_delimitor(char **value, int *i, int *j);
char		*process_quotes_in_delimitor(char **value);
char		*expand_envvar_in_heredoc(char *str, int *i, int *j, char **s1);

//********** EXECUTOR **********//
void		executor(t_cmd_line *cmdl, char ***env);
void		exec_bin(t_cmd_line *cmdl, char **env);
void		cmd_pathfinder(char **pcmd, char **env);

//********** BUILTINS **********//
void		builtin_echo(int ac, char **av, int fdout);
void		builtin_pwd(int ac, int fdout);
void		builtin_cd(int ac, char **av, char ***penv);
void		builtin_env(int ac, char **env, int fdout);
void		builtin_unset(int ac, char **av, char ***penv);
void		builtin_export(int ac, char **av, char ***penv, int fdout);
void		builtin_exit(int ac, char **av);

//********** ERRORS **********//
void		err_cmd_not_found(t_sh *sh, char *cmd);
void		err_export_invalid(t_sh *sh, char *key);
void		err_exit_invalid(t_sh *sh, char *str);
void		err_unset_invalid(t_sh *sh, char *key);

//********** UTILS **********//
int			str_has_only_spaces(char *str);
int			str_has_charset(char *str, char *charset);
int			str_has_quotes(char *str);
int			str_has_dollar_without_quotes(char *str);
int			str_has_space_without_quotes(char *str);
int			open_file_check(int fd, char *filename);
int			ft_str_tbl_len(char **tbl);
void		set_error_exit_status(t_sh *sh, int status);

//********** INT_CHECK **********//
char		*ft_itoa(int n);
int			str_is_int(char *str);

//********** MULTIPIPE **********//
void		execute_pipes(t_sh *sh);
void		wait_child(t_cmd_line *cmdl, int status, t_sh *sh);

//********** MAIN **********//
int			check_exec_bin(t_cmd_line *cmdl, char **env);

#endif
