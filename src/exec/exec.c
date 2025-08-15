/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:41:49 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/15 23:19:27 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handle_tilde(t_sys *sys)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(get_home_dir(sys), 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

/**
 * execute_cmd - Execute command
 *
 * @param node AST linked list
 * @param sys system struct
 *
 * @return Exit code from command.
 */
int	execute_cmd(t_ast *node, t_sys *sys)
{
	int	i;
	int	exit_status;

	i = 0;
	if (!node->args || !node->args[0])
		return (0);
	if (!node->args[0][0])
		return (ft_putstr_fd("minishell: command not found\n", 2), 127);
	if (!ft_strcmp(node->args[0], "~"))
		return (handle_tilde(sys), 126);
	if (is_builtin(node->args[0]) == 2)
		return (execute_builtin(node, sys));
	if (!ft_strncmp(node->args[0], "./minishell", 11))
	{
		signal(SIGINT, SIG_IGN);
		i = 1;
	}
	exit_status = execute_forked_cmd(node, sys);
	if (i == 1)
		setup_signals();
	return (exit_status);
}

/**
 * execute - execute parsed ast
 *
 * @param node AST linked list
 * @param sys system struct
 *
 * @return 1 = error. 0 = no error.
 */
int	execute(t_ast *node, t_sys *sys)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (handle_pipe(node, sys));
	else if (node->type >= AST_REDIR_IN && node->type <= AST_HEREDOC)
		return (handle_redirection(node, sys));
	else if (node->type == AST_CMD)
		return (execute_cmd(node, sys));
	else if (node->type == AST_AND)
	{
		status = execute(node->left, sys);
		if (status == 0)
			return (execute(node->right, sys));
		return (status);
	}
	else if (node->type == AST_OR)
	{
		status = execute(node->left, sys);
		if (status != 0)
			return (execute(node->right, sys));
		return (status);
	}
	return (1);
}

static int	process_line(char *line, t_sys *sys)
{
	t_ast	*ast;
	int		status;

	if (!line || !*line)
		return (0);
	ast = parse_line(line, sys);
	if (!ast)
	{
		if (sys->exit_status == 2)
			return (2);
		return (1);
	}
	status = execute(ast, sys);
	free_ast(ast);
	sys->exit_status = status;
	return (status);
}

int	shell_loop(t_sys *sys)
{
	char	*line;

	while (!sys->exit)
	{
		if (g_signal == SIG_INTERRUPT)
		{
			sys->exit_status = 130;
			g_signal = SIG_NONE;
		}
		line = readline(PROMPT);
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*line)
			add_history(line);
		process_line(line, sys);
		free(line);
	}
	return (sys->exit_status);
}
