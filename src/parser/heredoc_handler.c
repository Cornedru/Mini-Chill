/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/16 04:01:46 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_heredoc_data	*create_heredoc_data(char *delimiter, t_sys *sys)
{
	t_heredoc_data	*data;

	data = gc_malloc(sizeof(t_heredoc_data));
	if (!data)
		return (NULL);
	data->delimiter = gc_strdup(delimiter);
	data->expand = sys->hd_exp;
	data->tmp_filename = generate_tmp_filename();
	data->fd = -1;
	return (data);
}

static int	heredoc_child_process(t_heredoc_data *data, char *delimiter,
		t_sys *sys)
{
	int	result;

	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	result = read_heredoc_content(data, delimiter, sys);
	close(data->fd);
	gc_destroy();
	rl_clear_history();
	if (result == -1)
		exit(130);
	exit(0);
}

t_heredoc_data	*get_heredoc_data(char *delimiter, t_sys *sys)
{
	t_heredoc_data	*data;
	pid_t			pid;
	int				status;

	data = create_heredoc_data(delimiter, sys);
	if (!data)
		return (NULL);
	data->fd = open(data->tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (data->fd == -1)
		return (clean_heredoc_data(data), NULL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (close(data->fd), clean_heredoc_data(data), NULL);
	if (pid == 0)
		heredoc_child_process(data, delimiter, sys);
	close(data->fd);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		sys->exit_status = 130;
		return (clean_heredoc_data(data), NULL);
	}
	return (data);
}

void	clean_heredoc_data(t_heredoc_data *data)
{
	if (!data)
		return ;
	if (data->tmp_filename)
	{
		unlink(data->tmp_filename);
		gc_free(data->tmp_filename);
	}
	if (data->delimiter)
		gc_free(data->delimiter);
	gc_free(data);
}
