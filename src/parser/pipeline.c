/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/15 21:42:36 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_initial_pipe_error(t_token **tokens)
{
	if (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

static int	check_pipe_syntax_error(t_token **tokens)
{
	if (!*tokens || (*tokens)->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

static t_ast	*process_pipeline_loop(t_ast *left,
					t_token **tokens, t_sys *sys)
{
	t_ast	*right;

	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		if (check_pipe_syntax_error(tokens))
			return (free_ast(left), NULL);
		right = parse_command(tokens, sys);
		if (!right)
			return (free_ast(left), NULL);
		left = create_pipeline_node(left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast	*parse_pipeline(t_token **tokens, t_sys *sys)
{
	t_ast	*left;

	if (check_initial_pipe_error(tokens))
		return (NULL);
	left = parse_command(tokens, sys);
	if (!left)
		return (NULL);
	return (process_pipeline_loop(left, tokens, sys));
}
