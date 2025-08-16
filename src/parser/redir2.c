/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/16 04:12:34 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast	*make_heredoc_node(t_sys *sys, t_ast *node, t_token *filename)
{
	t_heredoc_data	*heredoc_data;

	heredoc_data = get_heredoc_data(filename->value, sys);
	if (!heredoc_data)
	{
		free_ast(node);
		return (NULL);
	}
	node->heredoc_data = heredoc_data;
	node->filename = gc_strdup(heredoc_data->tmp_filename);
	if (!node->filename)
	{
		clean_heredoc_data(heredoc_data);
		free_ast(node);
		return (NULL);
	}
	return (node);
}

static t_ast	*make_file_redir_node(t_ast *node, t_token *filename)
{
	node->filename = get_filename_from_t(filename);
	node->heredoc_data = NULL;
	if (!node->filename)
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}

static t_ast	*make_redir_node(t_sys *sys, t_ast *node, t_token *filename,
	t_ast_type redir_type)
{
	if (!node)
		return (NULL);
	if (redir_type == AST_HEREDOC)
		return (make_heredoc_node(sys, node, filename));
	else
		return (make_file_redir_node(node, filename));
}

t_ast	*parse_single_redirection(t_token **tokens, t_sys *sys)
{
	t_ast_type		redir_type;
	t_token			*filename_token;
	t_ast			*node;

	if (!is_redirection_token((*tokens)->type))
		return (NULL);
	redir_type = get_redirection_type((*tokens)->type);
	if (!redir_type)
		return (NULL);
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (NULL);
	}
	filename_token = *tokens;
	*tokens = (*tokens)->next;
	node = new_ast_node(redir_type);
	return (make_redir_node(sys, node, filename_token, redir_type));
}
