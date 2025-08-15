/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:26:32 by oligrien          #+#    #+#             */
/*   Updated: 2025/04/29 22:52:51 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapi;
	int		i;

	mapi = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!mapi || !f)
		return (NULL);
	i = -1;
	while (s[++i])
		mapi[i] = f(i, s[i]);
	mapi[i] = '\0';
	return (mapi);
}
