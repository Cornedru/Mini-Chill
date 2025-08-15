/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 04:17:38 by oligrien          #+#    #+#             */
/*   Updated: 2025/04/28 07:14:41 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_free(void **ptr)
{
	if (!ptr)
		return ;
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	ft_free_strarr(void ***ptr)
{
	int	i;

	if (!ptr || !*ptr)
		return ;
	i = -1;
	while ((*ptr)[++i])
		ft_free((void **)&((*ptr)[i]));
	ft_free((void **)ptr);
}
