/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:05:35 by oligrien          #+#    #+#             */
/*   Updated: 2025/04/29 22:55:56 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*freejoin(char *buffer, char *read_buf)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, read_buf);
	ft_free((void *)&buffer);
	return (tmp);
}

static char	*leftover(char *buffer)
{
	char	*leftover;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_free((void *)&buffer), NULL);
	leftover = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		leftover[j++] = buffer[i++];
	ft_free((void *)&buffer);
	return (leftover);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*read_file(int fd, char *buffer)
{
	char	*read_buf;
	ssize_t	bytes;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	read_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, read_buf, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_free((void *)&read_buf), ft_free((void *)&buffer), NULL);
		read_buf[bytes] = '\0';
		buffer = freejoin(buffer, read_buf);
		if (ft_strchr(read_buf, '\n'))
			break ;
	}
	ft_free((void *)&read_buf);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = leftover(buffer);
	return (line);
}
