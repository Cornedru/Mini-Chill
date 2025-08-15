/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:46:54 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/10 07:31:46 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_consecutive_words(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type == TOKEN_WORD)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

char	**gather_all_words(t_token **tokens)
{
	t_token	*start;
	int		count;
	char	**argv;
	int		i;

	start = *tokens;
	count = count_word_tokens(start);
	argv = (char **)gc_malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		argv[i] = gc_strdup((*tokens)->value);
		if (!argv[i])
			return (NULL);
		i++;
		*tokens = (*tokens)->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	count_split_entries(char **split)
{
	int	count;

	count = 0;
	while (split && split[count])
		count++;
	return (count);
}

char	**copy_and_merge(char **flat, char **split, int total, int count)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = (char **)gc_malloc(sizeof(char *) * (total + count + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < total)
	{
		tmp[i] = flat[i];
		i++;
	}
	j = 0;
	while (j < count)
	{
		tmp[i + j] = split[j];
		j++;
	}
	tmp[i + j] = NULL;
	return (tmp);
}

int	skip_whitespace(char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}
