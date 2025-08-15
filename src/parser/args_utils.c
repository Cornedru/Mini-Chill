/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/14 01:58:40 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast	*add_redirection(t_ast *redirs, t_ast *new_redir)
{
	t_ast	*last_redir;

	if (!redirs)
		return (new_redir);
	last_redir = redirs;
	while (last_redir->left)
		last_redir = last_redir->left;
	last_redir->left = new_redir;
	return (redirs);
}

int	handle_redirection_args(t_token **tokens, t_ast **redirs, t_ast **cmd,
		t_sys *sys)
{
	t_ast	*new_redir;

	(void)cmd;
	new_redir = parse_single_redirection(tokens, sys);
	if (!new_redir)
		return (-1);
	*redirs = add_redirection(*redirs, new_redir);
	return (0);
}

int	handle_word_args(t_token **tokens, t_ast **cmd, t_ast **redirs)
{
	char	**additional_args;

	(void)redirs;
	if (!*cmd)
	{
		*cmd = parse_simple_command(tokens);
		if (!*cmd)
			return (-1);
	}
	else
	{
		additional_args = gather_all_words(tokens);
		if (additional_args && additional_args[0])
		{
			(*cmd)->args = merge_args((*cmd)->args, additional_args);
			if (!(*cmd)->args)
				return (-1);
		}
	}
	return (0);
}

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
