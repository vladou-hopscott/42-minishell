/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:15 by vnafissi          #+#    #+#             */
/*   Updated: 2022/07/23 19:42:34 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Link global variable declared in main.c to this program */
extern t_sh	g_sh;

static void	handler(int sigtype, siginfo_t *siginfo, void *ucontext)
{
	(void)ucontext;
	(void)siginfo;
	if (sigtype == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sh.exit_status = 130;
	}
}

void	heredoc_handler(int sigtype)
{
	if (sigtype == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sh.error = 1;
		g_sh.exit_status = 130;
		ft_free_values_exit(&g_sh, 130, 1);
	}
}

void	sigquit_handler(int sigtype)
{
	if (sigtype == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sh.error = 1;
		g_sh.exit_status = 131;
		ft_free_values_exit(&g_sh, 131, 1);
	}
}

void	handle_signals(int activate_sigquit)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	if (activate_sigquit)
		signal(SIGQUIT, &sigquit_handler);
	else
		signal(SIGQUIT, SIG_IGN);
}
