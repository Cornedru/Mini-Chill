/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/14 03:07:29 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_sys	*sys;
	int		exit_status;

	(void)argc;
	(void)argv;
	setup_signals();
	if (init_shell(&sys, envp))
		return (1);
	exit_status = shell_loop(sys);
	gc_destroy();
	rl_clear_history();
	return (exit_status);
}
