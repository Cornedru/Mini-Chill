/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:50:11 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/06 23:18:59 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_pipe(t_ast *node, t_sys *sys)
{
	t_pipe_fork	ctx;
	int			status_l;
	int			status_r;

	if (pipe(ctx.pipe_fd) == -1)
		return (1);
	signal(SIGINT, SIG_IGN);
	if (fork_left(node, sys, &ctx))
		return (1);
	if (fork_right(node, sys, &ctx))
		return (1);
	close(ctx.pipe_fd[0]);
	close(ctx.pipe_fd[1]);
	waitpid(ctx.pid_l, &status_l, 0);
	waitpid(ctx.pid_r, &status_r, 0);
	setup_signals();
	if ((WIFSIGNALED(status_l) && WTERMSIG(status_l) == SIGINT)
		|| (WIFSIGNALED(status_r) && WTERMSIG(status_r) == SIGINT))
		return (130);
	if (WIFEXITED(status_r))
		return (WEXITSTATUS(status_r));
	return (1);
}
