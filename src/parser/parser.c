/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/15 21:58:31 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	char	**args;
	int		count;
	int		all_empty;

	if (!*tokens || (*tokens)->type != TOKEN_WORD)
		return (NULL);
	count = count_consecutive_words(*tokens);
	node = new_ast_node(AST_CMD);
	if (!node)
		return (NULL);
	args = allocate_args(count, node);
	if (!args)
		return (NULL);
	all_empty = fill_args_array(tokens, args, count);
	if (all_empty)
	{
		gc_free(args);
		free_ast(node);
		return (NULL);
	}
	node->args = args;
	return (node);
}

t_ast	*parse_command(t_token **tokens, t_sys *sys)
{
	t_ast	*cmd;
	t_ast	*redirs;

	if (!*tokens)
		return (NULL);
	cmd = NULL;
	redirs = collect_redirections_and_args(tokens, &cmd, sys);
	if (!cmd && !redirs)
		return (NULL);
	if (!cmd && redirs)
	{
		cmd = handle_empty_command(redirs);
		if (!cmd)
			return (NULL);
	}
	if (redirs)
		return (attach_redirections(cmd, redirs));
	return (cmd);
}

char	*process_segment(char *str, int *i, int seg_start, t_sys *sys)
{
	char	*temp;
	char	*var_value;
	char	*result;

	result = gc_strdup("");
	if (*i > seg_start)
	{
		temp = gc_substr(str, seg_start, *i - seg_start);
		result = gc_strjoin_free_s1(result, temp);
	}
	if (*i < (int)ft_strlen(str) && str[*i] == '$')
	{
		var_value = expand_variable(str, i, sys);
		result = gc_strjoin_free_s1(result, var_value);
	}
	return (result);
}

static t_ast	*parse(t_token **tokens, t_sys *sys)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_and_or(tokens, sys));
}

t_ast	*parse_line(char *line, t_sys *sys)
{
	t_token	*tokens;
	t_ast	*ast;

	if (!are_quotes_closed(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		sys->exit_status = 2;
		return (NULL);
	}
	tokens = lexer(line);
	if (!tokens)
	{
		sys->exit_status = 2;
		return (NULL);
	}
	expand_tokens(&tokens, sys);
	if (!validate_syntax(tokens))
	{
		sys->exit_status = 2;
		return (free_tokens(tokens), NULL);
	}
	ast = parse(&tokens, sys);
	free_tokens(tokens);
	return (ast);
}
