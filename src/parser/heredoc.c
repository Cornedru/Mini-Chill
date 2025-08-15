/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/13 04:45:46 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*generate_tmp_filename(void)
{
	static int	heredoc_count = 0;
	char		*filename;
	char		*num_str;
	char		*pid_str;
	char		*tmp;

	num_str = gc_itoa(heredoc_count++);
	pid_str = gc_itoa(getpid());
	tmp = gc_strjoin("/tmp/.minishell_heredoc_", pid_str);
	filename = gc_strjoin(tmp, "_");
	gc_free(tmp);
	tmp = filename;
	filename = gc_strjoin(tmp, num_str);
	gc_free(tmp);
	gc_free(num_str);
	gc_free(pid_str);
	return (filename);
}

char	*expand_heredoc_line(char *line, t_sys *sys)
{
	char	*result;
	char	*temp;
	char	*var_value;
	int		i;
	int		seg_start;

	result = gc_strdup("");
	i = 0;
	while (line[i])
	{
		seg_start = i;
		while (line[i] && line[i] != '$')
			i++;
		if (i > seg_start)
		{
			temp = gc_substr(line, seg_start, i - seg_start);
			result = gc_strjoin_free_s1_s2(result, temp);
		}
		if (line[i] == '$')
		{
			var_value = expand_variable(line, &i, sys);
			result = gc_strjoin_free_s1_s2(result, var_value);
		}
	}
	return (result);
}
