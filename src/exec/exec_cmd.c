/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:53:11 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/16 00:03:22 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_builtin - Check if command if built-in
 *
 * @return 0 = not built-in. 1 = fork built-in. 2 = non fork built-in.
 */
int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"env"))
		return (1);
	if (!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"export") || !ft_strcmp(cmd, "exit"))
		return (2);
	return (0);
}

/**
 * execute_builtin - Execute built-in command
 *
 * @param node ast node containing command name
 * @param sys system structure
 *
 * @return Return value of called built-in function (exit code). 1 if call
 * failed.
 */
int	execute_builtin(t_ast *node, t_sys *sys)
{
	if (!ft_strcmp(node->args[0], "cd"))
		return (builtin_cd(node, sys));
	if (!ft_strcmp(node->args[0], "echo"))
		return (builtin_echo(node, sys));
	if (!ft_strcmp(node->args[0], "env"))
		return (builtin_env(sys));
	if (!ft_strcmp(node->args[0], "exit"))
		return (builtin_exit(node, sys));
	if (!ft_strcmp(node->args[0], "export"))
		return (builtin_export(node, sys));
	if (!ft_strcmp(node->args[0], "pwd"))
		return (builtin_pwd(sys));
	if (!ft_strcmp(node->args[0], "unset"))
		return (builtin_unset(node, sys));
	(void)node;
	(void)sys;
	return (1);
}

int	execute_external(t_ast *node, t_sys *sys)
{
	char	*cmd_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd_path = find_cmd_path(sys, node->args[0]);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		gc_destroy();
		exit(127);
	}
	execve(cmd_path, node->args, sys->envp);
	ft_putstr_fd("minishell: ", 2);
	perror(node->args[0]);
	gc_free(cmd_path);
	gc_destroy();
	exit(126);
}

static int	exec_wtermsig(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 2);
		return (131);
	}
	if (WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		return (130);
	}
	return (0);
}

int	execute_forked_cmd(t_ast *node, t_sys *sys)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (is_builtin(node->args[0]) == 1)
		{
			status = execute_builtin(node, sys);
			gc_destroy();
			exit(status);
		}
		else
			execute_external(node, sys);
	}
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status))
		return (exec_wtermsig(status));
	return (WEXITSTATUS(status));
}
