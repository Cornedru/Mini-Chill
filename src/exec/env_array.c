/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:18:30 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/06 01:15:39 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * dup_array - Duplicate array of strings
 *
 * @param array array to copy
 *
 * @return New array after copy.
 */
char	**dup_array(char **array)
{
	int		i;
	int		count;
	char	**new;

	count = 0;
	while (array[count])
		count++;
	new = (char **)gc_malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (++i < count)
		new[i] = gc_strdup(array[i]);
	new[i] = NULL;
	return (new);
}

/**
 * env_getarray - Make char **envp back from t_env *envp
 *
 * @param envp environment linked list
 *
 * @return envp array of strings.
 */
static char	**env_getarray(t_env *env_lst)
{
	int		i;
	int		count;
	char	**array;

	count = ft_envsize(env_lst);
	array = (char **)gc_malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (++i < count)
	{
		if (!env_lst->content)
			array[i] = gc_strdup(env_lst->var);
		else
			array[i] = gc_strjoin_free_s1(gc_strjoin(env_lst->var, "="),
					env_lst->content);
		env_lst = env_lst->next;
	}
	array[i] = NULL;
	return (array);
}

/**
 * update_env_array - Update environment array fo strings
 *
 * @param sys system struct
 *
 * @return 1 = error. 0 = no error.
 */
int	update_env_array(t_sys *sys)
{
	gc_free_array((void **)sys->envp);
	sys->envp = env_getarray(sys->env_lst);
	if (!sys->envp)
		return (1);
	return (0);
}
