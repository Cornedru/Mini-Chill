/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:59:51 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/14 03:04:25 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_whitespace_and_sign(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
		(*i)++;
	return (str[*i] != '\0');
}

static int	check_digits_and_trailing(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] < '0' || str[*i] > '9')
		{
			while (str[*i] == ' ' || str[*i] == '\t')
				(*i)++;
			return (str[*i] == '\0');
		}
		(*i)++;
	}
	return (1);
}

static int	is_valid_num(char *str)
{
	long long int	nb;
	int				fail;
	int				i;

	if (!str || !*str)
		return (0);
	i = 0;
	fail = 0;
	if (!skip_whitespace_and_sign(str, &i))
		return (0);
	if (!check_digits_and_trailing(str, &i))
		return (0);
	nb = ft_atoll(str, &fail);
	(void)nb;
	if (fail > 0)
		return (0);
	return (1);
}

static int	exit_error(t_ast *node, t_sys *sys, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		sys->exit_status = 1;
		return (sys->exit_status);
	}
	if (error == 2)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		sys->exit = 1;
		sys->exit_status = 2;
		return (sys->exit_status);
	}
	return (0);
}

/**
 * builtin_exit
 *
 * @param node AST linked list
 * @param sys system struct
 *
 * @return Exit status
 */
int	builtin_exit(t_ast *node, t_sys *sys)
{
	if (!node->args[1])
		sys->exit = 1;
	else if (node->args[2])
	{
		if (is_valid_num(node->args[1]))
			return (exit_error(node, sys, 1));
		else
			return (exit_error(node, sys, 2));
	}
	else if (is_valid_num(node->args[1]) || !ft_strcmp(node->args[1], "--"))
	{
		sys->exit = 1;
		sys->exit_status = ft_atoll(node->args[1], NULL) % 256;
		if (sys->exit_status < 0)
			sys->exit_status = 256 + sys->exit_status;
	}
	else
		return (exit_error(node, sys, 2));
	ft_putstr_fd("exit \n", 2);
	return (sys->exit_status);
}
