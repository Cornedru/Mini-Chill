/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/15 21:42:58 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_token_value(char *str, t_sys *sys)
{
	char	*result;
	char	*segment_result;
	int		i;
	int		start;

	result = gc_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			handle_quote_section(str, &i, &result, sys);
		else
		{
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			segment_result = expand_outside_quotes(str, start, i, sys);
			result = gc_strjoin_free_s1(result, segment_result);
		}
	}
	return (result);
}

static t_token	*build_split_list(char **split)
{
	t_token	*head;
	t_token	*tail;
	t_token	*new_tok;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (split[i])
	{
		new_tok = create_token(TOKEN_WORD, split[i]);
		if (!head)
			head = new_tok;
		else
			tail->next = new_tok;
		tail = new_tok;
		i++;
	}
	return (head);
}

static void	replace_token_list(t_token **tokens_ptr, t_token **prev,
	t_token *current, char *expanded)
{
	t_token	*head;
	t_token	*tail;
	char	**split;
	t_token	*next;

	split = ft_split(expanded, ' ');
	if (!split)
		return ;
	head = build_split_list(split);
	if (!*prev)
		*tokens_ptr = head;
	else
		(*prev)->next = head;
	tail = head;
	next = current->next;
	while (tail && tail->next)
		tail = tail->next;
	tail->next = next;
	gc_free_array((void **)split);
	gc_free(current->value);
	gc_free(current);
}

static void	handle_expansion(t_token **tokens_ptr,
	t_token **prev, t_token **current, t_sys *sys)
{
	t_token	*next;
	char	*expanded;

	next = (*current)->next;
	if (*prev && (*prev)->type == TOKEN_HEREDOC
		&& !has_quotes((*current)->value))
		sys->hd_exp = 1;
	else
		sys->hd_exp = 0;
	expanded = expand_token_value((*current)->value, sys);
	if (!expanded)
		return ;
	if (should_split_token((*current)->value, expanded))
	{
		replace_token_list(tokens_ptr, prev, *current, expanded);
		if (*prev)
			*current = (*prev)->next;
		else
			*current = *tokens_ptr;
	}
	else
	{
		gc_free((*current)->value);
		(*current)->value = expanded;
	}
}

void	expand_tokens(t_token **tokens_ptr, t_sys *sys)
{
	t_token	*prev;
	t_token	*current;

	prev = NULL;
	current = *tokens_ptr;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			handle_expansion(tokens_ptr, &prev, &current, sys);
		prev = current;
		current = current->next;
	}
}
