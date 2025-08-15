/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/14 02:44:18 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast	*make_redir_node(t_sys *sys, t_ast *node, t_token *filename,
	t_ast_type redir_type)
{
	t_heredoc_data	*heredoc_data;

	if (!node)
		return (NULL);
	if (redir_type == AST_HEREDOC)
	{
		heredoc_data = get_heredoc_data(filename->value, sys);
		if (!heredoc_data)
			return (free_ast(node), NULL);
		node->heredoc_data = heredoc_data;
		node->filename = gc_strdup(heredoc_data->tmp_filename);
	}
	else
	{
		node->filename = get_filename_from_token(filename);
		node->heredoc_data = NULL;
	}
	return (node);
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
