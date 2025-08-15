/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/11 22:43:36 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_operator_token(char *input, int i, char **value, t_token_type *type)
{
	i = extract_operator(input, i, value);
	if (!*value)
		return (-1);
	*type = get_operator_type(*value, 0);
	if (*type == TOKEN_INVALID)
	{
		gc_free(*value);
		return (-1);
	}
	return (i);
}

static int	parse_ansi_c_char(char c)
{
	if (c == 'n')
		return ('\n');
	if (c == 't')
		return ('\t');
	if (c == 'r')
		return ('\r');
	if (c == '\\')
		return ('\\');
	if (c == '\'')
		return ('\'');
	return (c);
}

static void	parse_ansi_c_copy(char *raw, char *ansi)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (raw[j])
	{
		if (raw[j] == '\\' && raw[j + 1])
		{
			j++;
			ansi[k++] = parse_ansi_c_char(raw[j]);
		}
		else
			ansi[k++] = raw[j];
		j++;
	}
	ansi[k] = 0;
}

int	parse_ansi_c_quoted(char *input, int i, char **value, t_token_type *type)
{
	int		start;
	int		end;
	char	*raw;
	char	*ansi;

	start = i + 2;
	end = start;
	while (input[end] && input[end] != '\'')
		end++;
	if (input[end] == '\'')
	{
		raw = gc_substr(input, start, end - start);
		ansi = gc_malloc(end - start + 1);
		parse_ansi_c_copy(raw, ansi);
		*value = gc_strdup(ansi);
		gc_free(raw);
		gc_free(ansi);
		*type = TOKEN_WORD;
		return (end + 1);
	}
	return (-1);
}
