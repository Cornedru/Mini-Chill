/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:46:30 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/01 04:20:26 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"
// #include "stdio.h"

/**
 * gc_get_head - set pointer to gc head
 * 
 * Static variable!
 * 
 * Return: head address.
 */
t_mem	**gc_get_head(void)
{
	static t_mem	*head = NULL;

	return (&head);
}

void	gc_free_node(t_mem **node)
{
	free((*node)->mem);
	free(*node);
}

/* void	*gc_track(void *ptr)
{
	t_mem *node = malloc(sizeof(t_mem));
	if (!node)
		return (NULL);
	node->mem = ptr;
	node->next = *gc_get_head();
	*gc_get_head() = node;
	return (ptr);
} */

/* void	gc_print_leaks(void)
{
	t_mem *curr = *gc_get_head();
	int count = 0;

	while (curr)
	{
		printf("🔴 Leak %d → %p\n", ++count, curr->mem);
		curr = curr->next;
	}
	if (count == 0)
		printf("✅ No memory leaks detected!\n");
	else
		printf("⚠️  Total leaks: %d\n", count);
} */
