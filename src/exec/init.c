/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:59:21 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/16 04:52:28 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_shlvl(t_sys *sys)
{
	char	*tmp;
	char	*new_shlvl_str;
	int		shlvl;

	tmp = get_env_var("SHLVL", sys->env_lst);
	if (tmp)
	{
		shlvl = ft_atoi(tmp);
		shlvl++;
		if (shlvl > 1000)
		{
			ft_putstr_fd("bash: warning: shell level (", 2);
			ft_putnbr_fd(shlvl, 2);
			ft_putstr_fd(") too high, resetting to 1\n", 2);
			shlvl = 1;
		}
		else if (shlvl < 0)
			shlvl = 0;
	}
	else
		shlvl = 1;
	new_shlvl_str = ft_itoa(shlvl);
	set_env_var(sys, &sys->env_lst, "SHLVL", new_shlvl_str);
	free(new_shlvl_str);
}

/**
 * pull_env -  copy envp array into linked list
 *
 * @param envp environment array of strings
 *
 * @return env_lst environment linked list.
 */
static t_env	*pull_env(char **envp)
{
	t_env	*env_lst;
	char	*var;
	char	*content;
	char	*equal_sign;
	int		i;

	env_lst = NULL;
	i = -1;
	while (envp[++i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			var = gc_substr(envp[i], 0, equal_sign - envp[i]);
			content = gc_strdup(equal_sign + 1);
		}
		else
		{
			var = gc_strdup(envp[i]);
			content = NULL;
		}
		ft_envadd_back(&env_lst, gc_envnew(var, content));
	}
	return (env_lst);
}

static t_env	*create_env(t_sys *sys)
{
	char	**envp;
	char	*pwd;
	char	*underscore;

	envp = (char **)gc_malloc(sizeof(char *) * 5);
	pwd = getcwd(NULL, 0);
	envp[0] = gc_strjoin_free_s2("PWD=", pwd);
	free(pwd);
	envp[1] = gc_strdup("SHLVL=0");
	pwd = getcwd(NULL, 0);
	underscore = gc_strjoin(pwd, "/./minishell");
	envp[2] = gc_strjoin_free_s2("_=", underscore);
	envp[3] = gc_strjoin("PATH=",
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	sys->path_hide = 1;
	envp[4] = NULL;
	free(pwd);
	return (pull_env(envp));
}

/**
 * init_sys - initialize system struct
 *
 * @param sys system struct
 * @param envp environment array of strings
 *
 * @return 1 = error. 0 = no error.
 */
static int	init_sys(t_sys **sys, char **envp)
{
	*sys = (t_sys *)gc_malloc(sizeof(t_sys));
	if (!*sys)
		return (1);
	if (*envp)
	{
		(*sys)->env_lst = pull_env(envp);
		(*sys)->path_hide = 0;
	}
	else
		(*sys)->env_lst = create_env(*sys);
	(*sys)->envp = dup_array(envp);
	if (!(*sys)->env_lst || !(*sys)->envp)
		return (1);
	(*sys)->token = NULL;
	(*sys)->ast = NULL;
	(*sys)->exit = 0;
	(*sys)->exit_status = 0;
	return (0);
}

/**
 * init_shell - initialize shell program
 *
 * @param sys system struct
 * @param envp environment array of strings
 *
 * @return 1 = error. 0 = no error.
 */
int	init_shell(t_sys **sys, char **envp)
{
	int	error;

	error = 0;
	error = init_sys(sys, envp);
	error = update_env_array(*sys);
	set_shlvl(*sys);
	return (error);
}
