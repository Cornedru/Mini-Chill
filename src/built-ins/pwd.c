/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 03:03:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/01 23:31:29 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * builtin_pwd
 *
 * @return 1 = error. 0 = no error.
 */
int	builtin_pwd(t_sys *sys)
{
	char	*wd;

	wd = get_env_var("PWD", sys->env_lst);
	if (wd)
		printf("%s\n", wd);
	else
	{
		wd = getcwd(NULL, 0);
		if (!wd)
		{
			perror("pwd");
			ft_free((void *)&wd);
			return (1);
		}
		printf("%s\n", wd);
		ft_free((void *)&wd);
	}
	return (0);
}
