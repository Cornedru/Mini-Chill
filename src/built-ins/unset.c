/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:47:09 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/06 23:02:00 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_arg(t_sys *sys, char *arg)
{
	int	error;

	if (is_valid_identifier(arg))
		error = unset_env_var(sys, &sys->env_lst, arg);
	else
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		error = 1;
	}
	return (error);
}

/**
 * builtin_unset
 *
 * @param node AST linked list
 * @param sys system struct
 *
 * @return 1 = error. 0 = no error.
 */
int	builtin_unset(t_ast *node, t_sys *sys)
{
	int	i;
	int	error;

	if (!node->args[1])
		return (0);
	error = 0;
	i = 1;
	while (node->args[i])
	{
		if (handle_arg(sys, node->args[i]))
			error = 1;
		i++;
	}
	if (error)
		return (1);
	return (error);
}
