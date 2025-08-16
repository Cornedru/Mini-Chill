/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:46:30 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/16 04:00:39 by ndehmej          ###   ########.fr       */
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
