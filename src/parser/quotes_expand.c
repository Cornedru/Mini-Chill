/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 03:36:01 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/15 21:42:41 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_quoted_content(char *str, t_expand_params *params, t_sys *sys)
{
	char	*result;
	int		i;
	int		seg_start;

	if (params->quote == '\'')
		return (gc_substr(str, params->start, params->end - params->start));
	result = gc_strdup("");
	i = params->start;
	while (i < params->end)
	{
		seg_start = i;
		while (i < params->end && str[i] != '$')
			i++;
		result = gc_strjoin_free_s1(result, process_segment(str, &i, seg_start,
					sys));
	}
	return (result);
}

char	*expand_outside_quotes(char *str, int start, int end, t_sys *sys)
{
	char	*result;
	int		i;
	int		seg_start;

	result = gc_strdup("");
	i = start;
	while (i < end)
	{
		seg_start = i;
		while (i < end && str[i] != '$')
			i++;
		result = gc_strjoin_free_s1(result, process_segment(str, &i, seg_start,
					sys));
	}
	return (result);
}
