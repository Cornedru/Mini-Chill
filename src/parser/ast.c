/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:19:28 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/08 22:16:29 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*new_ast_node(t_ast_type type)
{
	t_ast	*node;

	node = gc_malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(t_ast));
	node->type = type;
	return (node);
}

t_ast	*create_pipeline_node(t_ast *left, t_ast *right)
{
	t_ast	*pipeline;

	pipeline = new_ast_node(AST_PIPE);
	if (!pipeline)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	pipeline->left = left;
	pipeline->right = right;
	return (pipeline);
}

void	free_ast(t_ast *ast)
{
	int	i;

	if (!ast)
		return ;
	if (ast->args)
	{
		i = 0;
		while (ast->args[i])
		{
			gc_free(ast->args[i]);
			i++;
		}
		gc_free(ast->args);
	}
	if (ast->filename)
		gc_free(ast->filename);
	if (ast->heredoc_data)
		clean_heredoc_data(ast->heredoc_data);
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	gc_free(ast);
}
