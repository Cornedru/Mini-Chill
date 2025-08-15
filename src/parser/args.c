/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/15 22:13:33 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

char	**merge_args(char **old_args, char **new_args)
{
	char	**result;
	int		old_count;
	int		new_count;
	int		i;
	int		j;

	old_count = count_args(old_args);
	new_count = count_args(new_args);
	result = (char **)gc_malloc(sizeof(char *) * (old_count + new_count + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < old_count)
		result[i] = old_args[i];
	j = -1;
	while (++j < new_count)
		result[i + j] = new_args[j];
	result[i + j] = NULL;
	gc_free(old_args);
	gc_free(new_args);
	return (result);
}

t_ast	*safe_free_ast(t_ast **a, t_ast **b)
{
	if (a && *a && (!b || *a != *b))
	{
		free_ast(*a);
		*a = NULL;
	}
	if (b && *b)
	{
		free_ast(*b);
		*b = NULL;
	}
	return (NULL);
}

t_ast	*collect_redirections_and_args(t_token **tokens, t_ast **cmd,
		t_sys *sys)
{
	t_ast	*redirs;

	redirs = NULL;
	*cmd = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR)
	{
		if (is_redirection_token((*tokens)->type))
		{
			if (handle_redirection_args(tokens, &redirs, cmd, sys) == -1)
				return (safe_free_ast(&redirs, cmd));
		}
		else if ((*tokens)->type == TOKEN_WORD)
		{
			if (handle_word_args(tokens, cmd, &redirs) == -1)
				return (safe_free_ast(&redirs, cmd));
		}
		else
			break ;
	}
	return (redirs);
}
