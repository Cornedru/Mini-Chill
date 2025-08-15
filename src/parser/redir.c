/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/13 22:04:11 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*attach_redirections(t_ast *cmd, t_ast *redir)
{
	t_ast	*temp;

	if (!redir)
		return (cmd);
	temp = redir;
	while (temp->left)
		temp = temp->left;
	temp->left = cmd;
	return (redir);
}

int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}

int	check_redirection_syntax(t_token *curr)
{
	if (!curr->next || curr->next->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!curr->next)
			ft_putstr_fd("newline", 2);
		else if (curr->next->type == TOKEN_PIPE)
			ft_putstr_fd("|", 2);
		else if (is_redirection_token(curr->next->type))
			ft_putstr_fd(curr->next->value, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

t_ast_type	get_redirection_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (AST_REDIR_IN);
	else if (token_type == TOKEN_REDIR_OUT)
		return (AST_REDIR_OUT);
	else if (token_type == TOKEN_REDIR_APPEND)
		return (AST_REDIR_APPEND);
	else if (token_type == TOKEN_HEREDOC)
		return (AST_HEREDOC);
	return (0);
}
