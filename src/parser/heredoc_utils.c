/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/13 22:22:54 by oligrien         ###   ########.fr       */
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
	char *clean_delimiter, t_sys *sys)
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

static int	handle_eof_or_interrupt(char *line, char *clean_delimiter)
{
	if (heredoc_interrupted(-1))
	{
		if (line)
			free(line);
		gc_free(clean_delimiter);
		return (-1);
	}
	if (!line)
	{
		ft_putstr_fd("minishell: warning:", 2);
		ft_putstr_fd("here-document delimited by end-of-file\n", 2);
		gc_free(clean_delimiter);
		return (0);
	}
	return (-2);
}

int	read_heredoc_content(t_heredoc_data *data, char *delimiter, t_sys *sys)
{
	char	*line;
	char	*clean_delimiter;
	int		status;

	clean_delimiter = remove_quotes(delimiter);
	heredoc_interrupted(0);
	while (1)
	{
		line = readline("> ");
		status = handle_eof_or_interrupt(line, clean_delimiter);
		if (status != -2)
			return (status);
		if (handle_heredoc_line(data, line, clean_delimiter, sys))
		{
			gc_free(clean_delimiter);
			return (0);
		}
	}
}

int	heredoc_interrupted(int b)
{
	static int	interrupted_status = 0;

	if (b != -1)
		interrupted_status = b;
	return (interrupted_status);
}
