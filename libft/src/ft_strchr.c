/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:05:21 by oligrien          #+#    #+#             */
/*   Updated: 2025/04/27 04:05:59 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		while (*s && *s != (unsigned char)c)
			s++;
		if (*s == (unsigned char)c)
			return ((char *)s);
	}
	return (NULL);
}
