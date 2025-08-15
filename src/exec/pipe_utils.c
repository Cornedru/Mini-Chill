/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:54:16 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/06 23:19:05 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	contains_heredoc(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == AST_HEREDOC)
		return (1);
	return (contains_heredoc(node->left) || contains_heredoc(node->right));
}

static void	left_child(t_ast *node, t_sys *sys, int *pipe_fd)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	status = execute(node->left, sys);
	gc_destroy();
	exit(status);
}

static void	right_child(t_ast *node, t_sys *sys, int *pipe_fd)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[1]);
	if (!contains_heredoc(node->right))
		dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	status = execute(node->right, sys);
	gc_destroy();
	exit(status);
}

int	fork_left(t_ast *node, t_sys *sys, t_pipe_fork *fd)
{
	fd->pid_l = fork();
	if (fd->pid_l == -1)
	{
		close(fd->pipe_fd[0]);
		close(fd->pipe_fd[1]);
		setup_signals();
		return (1);
	}
	if (fd->pid_l == 0)
		left_child(node, sys, fd->pipe_fd);
	return (0);
}

int	fork_right(t_ast *node, t_sys *sys, t_pipe_fork *fd)
{
	fd->pid_r = fork();
	if (fd->pid_r == -1)
	{
		close(fd->pipe_fd[0]);
		close(fd->pipe_fd[1]);
		kill(fd->pid_l, SIGTERM);
		waitpid(fd->pid_l, NULL, 0);
		setup_signals();
		return (1);
	}
	if (fd->pid_r == 0)
		right_child(node, sys, fd->pipe_fd);
	return (0);
}
