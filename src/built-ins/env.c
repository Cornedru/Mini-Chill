/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 00:38:16 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/04 03:21:21 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * builtin_env
 *
 * @param sys system struct
 *
 * @return 0 = no error.
 */
int	builtin_env(t_sys *sys)
{
	t_env	*current;

	current = sys->env_lst;
	while (current)
	{
		if (current->content)
		{
			if (!(!ft_strcmp("PATH", current->var) && sys->path_hide))
				printf("%s=%s\n", current->var, current->content);
		}
		current = current->next;
	}
	return (0);
}
