/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:09:10 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/15 22:21:06 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"
#include <stdio.h>

/**
 * gc_malloc - allocate memory on the heap but also
 *    add the allocated memory to a linked list
 *
 * @size: the size of the memory to be allocated
 *
 * @head: the address of the head of the linked list
 *
 * Return: Nothing.
 */
void	*gc_malloc(size_t size)
{
	t_mem	**head;
	t_mem	*node;

	if (!size)
		return (NULL);
	head = gc_get_head();
	node = (t_mem *)malloc(sizeof(t_mem));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(t_mem));
	node->mem = malloc(size);
	if (!node->mem)
	{
		free(node);
		return (NULL);
	}
	ft_bzero(node->mem, size);
	node->next = *head;
	*head = node;
	return (node->mem);
}

/**
 * gc_free - free an allocated memory
 *    and also remove it from the linked list
 *
 * @mem: memory to be freed
 *
 * Return: Nothing.
 */
void	gc_free(void *mem)
{
	t_mem	**current_ptr;
	t_mem	*node_to_del;

	if (!mem)
		return ;
	current_ptr = gc_get_head();
	while (*current_ptr)
	{
		if ((*current_ptr)->mem == mem)
		{
			node_to_del = *current_ptr;
			*current_ptr = node_to_del->next;
			gc_free_node(&node_to_del);
			return ;
		}
		current_ptr = &(*current_ptr)->next;
	}
}

void	gc_free_array(void **mem)
{
	int	i;

	if (!mem)
		return ;
	i = -1;
	while (mem[++i])
		gc_free(mem[i]);
	gc_free(mem);
}

/**
 * gc_destroy - free all and destroy gc.
 *
 * Return: Nothing.
 */
void	gc_destroy(void)
{
	t_mem	**head;
	t_mem	*current;
	t_mem	*tmp;

	head = gc_get_head();
	current = *head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->mem);
		free(tmp);
	}
	*head = NULL;
}
