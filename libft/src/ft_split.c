/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:26:32 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/10 07:13:27 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../../includes/minishell.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*strndup_gc(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = gc_malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[n] = '\0';
	return (dup);
}

char	**ft_split(const char *s, char c)
{
	size_t		i;
	size_t		word_count;
	char		**res;
	const char	*start;

	i = 0;
	word_count = count_words(s, c);
	res = gc_malloc(sizeof(char *) * (word_count + 1));
	if (!res || !s)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = s;
			while (*s && *s != c)
				s++;
			res[i] = strndup_gc(start, s - start);
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
