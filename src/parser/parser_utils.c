/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/14 02:01:38 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**echo_args(char **args)
{
	int		i;
	int		total;
	char	**flat;
	char	**split;
	int		count;

	i = 0;
	total = 0;
	flat = NULL;
	while (args && args[i])
	{
		split = ft_split(args[i], ' ');
		count = count_split_entries(split);
		flat = copy_and_merge(flat, split, total, count);
		total += count;
		if (split)
			gc_free(split);
		i++;
	}
	return (flat);
}

char	*extract_env_value(char *str, int *i, int start, t_sys *sys)
{
	int		end;
	char	*key;
	char	*value;

	end = start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	key = gc_substr(str, start, end - start);
	if (!key)
		return (gc_strdup(""));
	value = get_env_var(key, sys->env_lst);
	*i = end;
	gc_free(key);
	if (value)
		return (gc_strdup(value));
	return (gc_strdup(""));
}

static t_ast	*create_and_or_node(t_ast *left, t_ast *right, t_ast_type type)
{
	t_ast	*node;

	node = new_ast_node(type);
	if (!node)
		return (free_ast(left), free_ast(right), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse_and_or(t_token **tokens, t_sys *sys)
{
	t_ast		*left;
	t_ast		*right;
	t_ast_type	type;

	left = parse_pipeline(tokens, sys);
	if (!left)
		return (NULL);
	if (!*tokens || ((*tokens)->type != TOKEN_AND
			&& (*tokens)->type != TOKEN_OR))
		return (left);
	if ((*tokens)->type == TOKEN_AND)
		type = AST_AND;
	else
		type = AST_OR;
	*tokens = (*tokens)->next;
	right = parse_and_or(tokens, sys);
	if (!right)
		return (free_ast(left), NULL);
	return (create_and_or_node(left, right, type));
}
