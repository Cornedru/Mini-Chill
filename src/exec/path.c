/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:54:16 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/06 23:02:16 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*pull_path(char **env_paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = -1;
	while (env_paths && env_paths[++i])
	{
		tmp = gc_strjoin(env_paths[i], "/");
		cmd_path = gc_strjoin(tmp, cmd);
		gc_free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		gc_free(cmd_path);
	}
	return (NULL);
}

/**
 * find_cmd_path - Find command path
 *
 * @param sys system struct
 * @param cmd command name
 *
 * @return 1 = error. 0 = no error.
 */
char	*find_cmd_path(t_sys *sys, char *cmd)
{
	char	**env_paths;
	char	*cmd_path;
	char	*tmp;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (gc_strdup(cmd));
		return (NULL);
	}
	tmp = get_env_var("PATH", sys->env_lst);
	env_paths = gc_split(tmp, ':');
	cmd_path = pull_path(env_paths, cmd);
	gc_free_array((void **)env_paths);
	return (cmd_path);
}

char	*get_home_dir(t_sys *sys)
{
	char			*home;
	uid_t			my_uid;
	struct passwd	*my_passwd;
	char			*dup;

	home = get_env_var("HOME", sys->env_lst);
	if (!home)
	{
		my_uid = getuid();
		my_passwd = getpwuid(my_uid);
		if (!my_passwd)
			return (NULL);
		dup = gc_strdup(my_passwd->pw_dir);
		return (dup);
	}
	return (home);
}
