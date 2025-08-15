/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:46:54 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/06 15:36:13 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_special_var(char *str, int *i, t_sys *sys)
{
	int	start;

	start = *i + 1;
	if (str[start] == '?')
	{
		*i = start + 1;
		return (gc_itoa(sys->exit_status));
	}
	if (str[start] == '$')
	{
		*i = start + 1;
		return (gc_itoa(getpid()));
	}
	if (str[start] == '\0' || str[start] == ' ' || str[start] == '\t'
		|| str[start] == '"' || str[start] == '\'')
	{
		*i = start;
		return (gc_strdup("$"));
	}
	return (NULL);
}

static char	*handle_invalid_or_numeric_var(char *str, int *i)
{
	int	start;

	start = *i + 1;
	if (!str[start] || (!ft_isalpha(str[start]) && str[start] != '_'
			&& !ft_isdigit(str[start])))
	{
		*i = start;
		return (gc_strdup("$"));
	}
	if (ft_isdigit(str[start]))
	{
		*i = start + 1;
		return (gc_strdup(""));
	}
	return (NULL);
}

char	*expand_variable(char *str, int *i, t_sys *sys)
{
	char	*res;
	int		start;

	res = expand_special_var(str, i, sys);
	if (res)
		return (res);
	res = handle_invalid_or_numeric_var(str, i);
	if (res)
		return (res);
	start = *i + 1;
	return (extract_env_value(str, i, start, sys));
}
