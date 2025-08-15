/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/12 03:38:24 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quote_section(char *str, int *i, char **result, t_sys *sys)
{
	t_expand_params	params;
	char			*segment_result;

	params.quote = str[*i];
	params.start = *i + 1;
	(*i)++;
	while (str[*i] && str[*i] != params.quote)
		(*i)++;
	params.end = *i;
	segment_result = expand_quoted_content(str, &params, sys);
	*result = gc_strjoin_free_s1(*result, segment_result);
	if (str[*i] == params.quote)
		(*i)++;
}

int	extract_word_with_quotes(char *input, int i, char **word)
{
	int		start;
	int		end;
	char	quote;

	start = i;
	end = i;
	while (input[end] && !is_operator(input[end]) && input[end] != ' '
		&& input[end] != '\t')
	{
		if (input[end] == '\'' || input[end] == '"')
		{
			quote = input[end];
			end++;
			while (input[end] && input[end] != quote)
				end++;
			if (input[end] == quote)
				end++;
		}
		else
			end++;
	}
	*word = gc_substr(input, start, end - start);
	return (end);
}
