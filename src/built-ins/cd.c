/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:01:04 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/09 04:24:05 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_error_path(char **args, char *path)
{
	if (args[1])
		return (args[1]);
	return (path);
}

static int	cd_error(char *msg, char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (errno == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", 2);
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	return (1);
}

static int	cd_set_env(t_sys *sys, char *old_pwd, char *new_pwd, char *path)
{
	if (chdir(new_pwd))
		return (cd_error(NULL, path), gc_free(new_pwd), gc_free(path), 1);
	if (set_env_var(sys, &sys->env_lst, "OLDPWD", old_pwd))
		return (gc_free(new_pwd), gc_free(path), 1);
	if (set_env_var(sys, &sys->env_lst, "PWD", new_pwd))
		return (gc_free(new_pwd), gc_free(path), 1);
	return (gc_free(new_pwd), gc_free(path), 0);
}

int	builtin_cd(t_ast *node, t_sys *sys)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;
	char	*error_path;

	if (node->args[1] && node->args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	path = get_path(sys->env_lst, node->args[1]);
	if (!path)
		return (1);
	old_pwd = get_env_var("PWD", sys->env_lst);
	if (!old_pwd)
		old_pwd = getcwd(NULL, 0);
	error_path = get_error_path(node->args, path);
	new_pwd = build_logical_path(old_pwd, path);
	if (!get_env_var("PWD", sys->env_lst) && old_pwd)
		free(old_pwd);
	if (!new_pwd)
		return (cd_error(NULL, error_path), gc_free(path), 1);
	if (node->args[1] && !ft_strcmp(node->args[1], "-"))
		return (cd_set_env(sys, old_pwd, new_pwd, error_path), \
			builtin_pwd(sys));
	return (cd_set_env(sys, old_pwd, new_pwd, error_path));
}
