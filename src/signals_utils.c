/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/16 21:57:46 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigquit_prompt(int sig)
{
	(void)sig;
	g_signal = 131;
	write(1, "Quit\n", 5);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_prompt(void)
{
	struct sigaction	act;
	struct sigaction	act_quit;

	ft_bzero(&act, sizeof(act));
	ft_bzero(&act_quit, sizeof(act_quit));
	act.sa_handler = sigint_prompt;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL)
}

void	set_signals_heredoc(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = heredoc_sigint_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_handler(int mode)
{
	if (mode == PROMPT_MODE)
		set_signals_prompt();
	else if (mode == HEREDOC_MODE)
		set_signals_heredoc();
}
