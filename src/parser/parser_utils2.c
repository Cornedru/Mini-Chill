/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/16 04:09:09 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**allocate_args(int count, t_ast *node)
{
	char	**args;

	args = (char **)gc_malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		free_ast(node);
		return (NULL);
	}
	return (args);
}

int	fill_args_array(t_token **tokens, char **args, int count)
{
	int	i;
	int	all_empty;

	i = 0;
	all_empty = 1;
	while (*tokens && (*tokens)->type == TOKEN_WORD && i < count)
	{
		args[i] = gc_strdup((*tokens)->value);
		if (args[i] && args[i][0] != '\0')
			all_empty = 0;
		*tokens = (*tokens)->next;
		i++;
	}
	args[i] = NULL;
	return (all_empty);
}

t_ast	*handle_empty_command(t_ast *redirs)
{
	t_ast	*cmd;

	cmd = new_ast_node(AST_CMD);
	if (!cmd)
		return (free_ast(redirs), NULL);
	cmd->args = NULL;
	return (cmd);
}

char	*get_filename_from_t(t_token *filename_token)
{
	char	*filename;

	filename = remove_quotes(filename_token->value);
	if (!filename)
		filename = gc_strdup(filename_token->value);
	return (filename);
}
