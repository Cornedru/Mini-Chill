/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:47:06 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/12 04:14:44 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	echo_print_args(char **args, int start, t_sys *sys)
{
	int		first;
	int		i;
	char	*home;
	char	*joined;

	first = 1;
	i = start;
	while (args && args[i])
	{
		if (!first)
			ft_putchar_fd(' ', 1);
		if (args[i][0] == '~' && (args[i][1] == '/' || !args[i][1]))
		{
			home = get_home_dir(sys);
			joined = ft_strjoin(home, args[i] + 1);
			ft_putstr_fd(joined, 1);
			gc_free(joined);
		}
		else
			ft_putstr_fd(args[i], 1);
		first = 0;
		i++;
	}
	return (i);
}

static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_ast *node, t_sys *sys)
{
	int		n;
	int		start;

	n = 0;
	start = 1;
	while (node->args && node->args[start] && is_n_option(node->args[start]))
	{
		n = 1;
		start++;
	}
	echo_print_args(node->args, start, sys);
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}
