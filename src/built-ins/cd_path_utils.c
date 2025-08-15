/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:01:04 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/09 05:23:17 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_not_a_dir(char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Not a directory\n", 2);
}

static char	*path_from_tilde(t_env *envp, char *arg)
{
	char	*home;

	home = get_env_var("HOME", envp);
	if (!home)
		return (NULL);
	return (gc_strjoin(home, arg + 1));
}

static char	*default_cd_path(t_env *envp)
{
	char	*home;

	home = get_env_var("HOME", envp);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (gc_strdup(home));
}

static char	*path_from_dash(t_env *envp)
{
	char	*path;

	path = get_env_var("OLDPWD", envp);
	if (!path)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	return (gc_strdup(path));
}

char	*get_path(t_env *envp, char *arg)
{
	if (arg && arg[0] == '\0')
		return (gc_strdup("."));
	if (!arg)
		return (default_cd_path(envp));
	if (!ft_strcmp(arg, "-"))
		return (path_from_dash(envp));
	if (arg[0] == '~')
		return (path_from_tilde(envp, arg));
	return (gc_strdup(arg));
}
