/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/09 02:16:21 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_word_tokens(t_token *start)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = start;
	while (tmp && tmp->type != TOKEN_PIPE && tmp->type != TOKEN_AND
		&& tmp->type != TOKEN_OR)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
			gc_free(tokens->value);
		gc_free(tokens);
		tokens = tmp;
	}
}

int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = tokens;
	if (curr && is_operator_token(curr->type))
		return (check_operator_syntax(curr, prev));
	while (curr)
	{
		if (is_redirection_token(curr->type))
		{
			if (!check_redirection_syntax(curr))
				return (0);
		}
		else if (is_operator_token(curr->type))
		{
			if (!check_operator_syntax(curr, prev))
				return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}
