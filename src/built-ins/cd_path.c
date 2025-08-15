/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:03:09 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/10 07:11:53 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	trim_last_component(char **path)
{
	char	*last;
	char	*new_str;

	if (!ft_strcmp(*path, "/"))
		return ;
	last = ft_strrchr(*path, '/');
	if (!last)
		return ;
	if (last - *path == 0)
		new_str = gc_strdup("/");
	else
		new_str = gc_substr(*path, 0, last - *path);
	gc_free(*path);
	*path = new_str;
}

static int	handle_symlink(char **path, char *test_path)
{
	struct stat	stat_buf;
	DIR			*dir;

	dir = opendir(test_path);
	if (dir)
		closedir(dir);
	else
		return (1);
	if (lstat(test_path, &stat_buf) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(test_path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (gc_free(test_path), 1);
	}
	if (S_ISDIR(stat_buf.st_mode) || S_ISLNK(stat_buf.st_mode))
	{
		gc_free(*path);
		*path = test_path;
		return (0);
	}
	else
		return (print_not_a_dir(test_path), gc_free(test_path), 2);
}

static int	handle_one_component(char **path, const char *component)
{
	char	*test_path;
	char	*tmp;

	if (!ft_strcmp(component, "."))
		return (0);
	if (!ft_strcmp(component, ".."))
		return (trim_last_component(path), 0);
	if (ft_strcmp(*path, "/") == 0)
		tmp = gc_strdup("/");
	else
		tmp = gc_strjoin(*path, "/");
	test_path = gc_strjoin_free_s1(tmp, component);
	return (handle_symlink(path, test_path));
}

static char	*resolve_path(char *base_path, char **components)
{
	char	*resolved_path;

	resolved_path = gc_strdup(base_path);
	while (components && *components)
	{
		if (handle_one_component(&resolved_path, *components))
			return (gc_free(resolved_path), NULL);
		components++;
	}
	return (resolved_path);
}

char	*build_logical_path(char *current_pwd, char *user_input)
{
	char	**components;
	char	*base_path;
	char	*final_path;

	components = gc_split(user_input, '/');
	if (user_input[0] == '/')
		base_path = gc_strdup("/");
	else
		base_path = gc_strdup(current_pwd);
	final_path = resolve_path(base_path, components);
	if (!final_path)
		return (gc_free(base_path), gc_free_array((void **)components), NULL);
	return (gc_free(base_path), gc_free_array((void **)components), final_path);
}
