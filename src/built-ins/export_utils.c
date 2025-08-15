/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:59:51 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/05 19:56:09 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_next_env(t_env *env_lst, char *last_printed)
{
	t_env	*candidat;
	t_env	*current;

	candidat = NULL;
	current = env_lst;
	while (current)
	{
		if ((!last_printed || ft_strcmp(current->var, last_printed) > 0)
			&& (!candidat || ft_strcmp(current->var, candidat->var) < 0))
			candidat = current;
		current = current->next;
	}
	return (candidat);
}

int	is_invalid_export_key(char *var, char *arg)
{
	if (!var || !*var || ft_strchr(var, ' ') || ft_strchr(var, '\t')
		|| !is_valid_env_var_name(var))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}
