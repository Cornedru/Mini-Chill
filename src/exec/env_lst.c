/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:30:28 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/04 02:21:16 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*ft_envlast(t_env *env_lst)
{
	while (env_lst && env_lst->next)
		env_lst = env_lst->next;
	return (env_lst);
}

void	free_envnode(t_env *env_lst)
{
	gc_free(env_lst->var);
	gc_free(env_lst->content);
	gc_free(env_lst);
}

int	ft_envsize(t_env *env_lst)
{
	int	cnt;

	cnt = 0;
	while (env_lst)
	{
		cnt++;
		env_lst = env_lst->next;
	}
	return (cnt);
}

t_env	*gc_envnew(char *var, char *content)
{
	t_env	*node;

	node = (t_env *)gc_malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->var = var;
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_envadd_back(t_env **env_lst, t_env *new)
{
	t_env	*last;

	if (!env_lst || !new)
		return ;
	if (*env_lst == NULL)
		*env_lst = new;
	else
	{
		last = ft_envlast(*env_lst);
		last->next = new;
	}
}
