/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:26:32 by oligrien          #+#    #+#             */
/*   Updated: 2025/04/27 04:11:12 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		cnt;

	if (!s1 && !set)
		return ((char *)s1);
	cnt = 0;
	i = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
	{
		cnt++;
		i--;
	}
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
	{
		cnt++;
		i++;
	}
	return (ft_substr(s1, i, ft_strlen(s1) - cnt));
}
