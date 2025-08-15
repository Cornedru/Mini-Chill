/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 01:43:55 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/09 22:26:24 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_env_line(t_env *candidat, t_sys *sys)
{
	if (!candidat->content && !(!ft_strcmp("PATH", candidat->var)
			&& sys->path_hide))
		printf("declare -x %s\n", candidat->var);
	else if (!(!ft_strcmp("PATH", candidat->var) && sys->path_hide))
		printf("declare -x %s=\"%s\"\n", candidat->var, candidat->content);
}

static void	env_print_sorted(t_env *env_lst, t_sys *sys)
{
	int		size;
	char	*last_printed;
	t_env	*candidat;

	size = ft_envsize(env_lst);
	last_printed = NULL;
	while (size--)
	{
		candidat = find_next_env(env_lst, last_printed);
		print_env_line(candidat, sys);
		last_printed = candidat->var;
	}
}

static void	parse_arg(char *arg, char **var, char **content, int *is_append)
{
	char	*plus_equal;
	char	*equal_sign;

	*is_append = 0;
	plus_equal = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus_equal)
	{
		*var = gc_substr(arg, 0, plus_equal - arg);
		*content = gc_strdup(plus_equal + 2);
		*is_append = 1;
		return ;
	}
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*var = gc_substr(arg, 0, equal_sign - arg);
		*content = gc_strdup(equal_sign + 1);
	}
	else
	{
		*var = gc_strdup(arg);
		*content = NULL;
	}
}

static int	handle_arg(t_sys *sys, char *arg)
{
	char	*var;
	char	*content;
	int		error;
	int		is_append;

	parse_arg(arg, &var, &content, &is_append);
	if (is_invalid_export_key(var, arg))
		return (gc_free(var), gc_free(content), 1);
	if (!is_append)
		error = set_env_var(sys, &sys->env_lst, var, content);
	else
		error = append_env_var(sys, &sys->env_lst, var, content);
	if (!ft_strncmp(arg, "PATH", 4))
		sys->path_hide = 0;
	gc_free(var);
	gc_free(content);
	return (error);
}

/**
 * builtin_export
 *
 * @param node AST linked list
 * @param sys system struct
 *
 * @return 1 = error. 0 = no error.
 */
int	builtin_export(t_ast *node, t_sys *sys)
{
	int	error;
	int	i;

	error = 0;
	if (!node->args[1])
		return (env_print_sorted(sys->env_lst, sys), 0);
	i = 0;
	while (node->args[++i])
	{
		if (handle_arg(sys, node->args[i]))
			error = 1;
	}
	if (error)
		return (1);
	return (0);
}
