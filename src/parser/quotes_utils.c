/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/13 04:46:35 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_quoted_content(char *str, int *i, int *j, char *result)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		result[(*j)++] = str[*i];
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
}

static int	count_quoted_chars(char *str, int *i)
{
	char	quote;
	int		len;

	quote = str[*i];
	(*i)++;
	len = 0;
	while (str[*i] && str[*i] != quote)
	{
		len++;
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
	return (len);
}

static int	get_unquoted_length(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			len += count_quoted_chars(str, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = (char *)gc_malloc(get_unquoted_length(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			copy_quoted_content(str, &i, &j, result);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	are_quotes_closed(const char *str)
{
	int	i;
	int	singleq;
	int	doubleq;

	i = 0;
	singleq = 0;
	doubleq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && doubleq % 2 == 0)
			singleq++;
		else if (str[i] == '"' && singleq % 2 == 0)
			doubleq++;
		i++;
	}
	if (singleq % 2 == 0 && doubleq % 2 == 0)
		return (1);
	return (0);
}
