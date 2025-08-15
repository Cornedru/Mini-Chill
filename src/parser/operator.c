/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:46:54 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/08 22:14:25 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

static int	get_operator_len(char *input, int i)
{
	if ((input[i] == '|' && input[i + 1] == '|') || (input[i] == '<' && input[i
				+ 1] == '<') || (input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '&' && input[i + 1] == '&'))
		return (2);
	return (1);
}

int	extract_operator(char *input, int i, char **op)
{
	int	len;

	len = get_operator_len(input, i);
	*op = gc_substr(input, i, len);
	return (i + len);
}

int	check_operator_syntax(t_token *curr, t_token *prev)
{
	if ((prev && is_operator_token(prev->type)) || !curr->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (curr->type == TOKEN_PIPE)
			ft_putstr_fd("|", 2);
		else if (curr->type == TOKEN_AND)
			ft_putstr_fd("&&", 2);
		else if (curr->type == TOKEN_OR)
			ft_putstr_fd("||", 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

t_token_type	get_operator_type(char *input, int i)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			return (TOKEN_OR);
		return (TOKEN_PIPE);
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (TOKEN_REDIR_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	else if (input[i] == '&')
	{
		if (input[i + 1] == '&')
			return (TOKEN_AND);
		return (TOKEN_INVALID);
	}
	return (TOKEN_WORD);
}
