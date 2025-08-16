/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/16 04:13:19 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_heredoc_line(t_heredoc_data *data, char *line, t_sys *sys)
{
	char	*expanded_line;

	if (data->expand && ft_strchr(line, '$'))
	{
		expanded_line = expand_heredoc_line(line, sys);
		write(data->fd, expanded_line, ft_strlen(expanded_line));
		gc_free(expanded_line);
	}
	else
		write(data->fd, line, ft_strlen(line));
	write(data->fd, "\n", 1);
	return (0);
}

static int	handle_heredoc_line(t_heredoc_data *data, char *line,
	t_sys *sys, char *clean_delimiter)
{
	if (ft_strcmp(line, clean_delimiter) == 0)
	{
		free(line);
		return (1);
	}
	write_heredoc_line(data, line, sys);
	free(line);
	return (0);
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "^C", 3);
	g_signal = SIGINT;
	heredoc_interrupted(1);
	rl_replace_line("", 0);
	rl_done = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

static int	heredoc_read_line(t_heredoc_data *data, t_sys *sys,
	char *clean_delimiter)
{
	char	*line;

	line = readline("> ");
	if (g_signal == SIGINT)
	{
		if (line)
			free(line);
		return (-1);
	}
	if (!line)
	{
		write(1, "warning: heredoc delimited by end-of-file\n", 43);
		return (1);
	}
	if (handle_heredoc_line(data, line, sys, clean_delimiter))
		return (1);
	return (0);
}

int	read_heredoc_content(t_heredoc_data *data, char *delimiter, t_sys *sys)
{
	char	*clean_delimiter;
	int		ret;

	clean_delimiter = remove_quotes(delimiter);
	g_signal = 0;
	rl_catch_signals = 0;
	signals_handler(HEREDOC_MODE);
	while (1)
	{
		ret = heredoc_read_line(data, sys, clean_delimiter);
		if (ret == -1)
		{
			gc_free(clean_delimiter);
			sys->last_status = 130;
			return (-1);
		}
		if (ret == 1)
		{
			gc_free(clean_delimiter);
			return (0);
		}
	}
}
