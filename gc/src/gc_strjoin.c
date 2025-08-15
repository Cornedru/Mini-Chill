/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 23:08:50 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/26 23:37:33 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gc.h"

char	*gc_strjoin(char *s1, char *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return ("");
	else if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)gc_malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		join[i + j] = s2[j];
	return (join);
}

char	*gc_strjoin_free_s1(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (gc_free((void *)s1), "");
	else if (!s1)
		return (gc_free((void *)s1), (char *)s2);
	else if (!s2)
		return (gc_free((void *)s1), (char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)gc_malloc(sizeof(char) * (len + 1));
	if (!join)
		return (gc_free((void *)s1), NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		join[i + j] = s2[j];
	return (gc_free((void *)s1), join);
}

char	*gc_strjoin_free_s2(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (gc_free((void *)s2), "");
	else if (!s1)
		return (gc_free((void *)s2), (char *)s2);
	else if (!s2)
		return (gc_free((void *)s2), (char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)gc_malloc(sizeof(char) * (len + 1));
	if (!join)
		return (gc_free((void *)s2), NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		join[i + j] = s2[j];
	return (gc_free((void *)s2), join);
}

char	*gc_strjoin_free_s1_s2(char const *s1, char const *s2)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (gc_free((void *)s1), gc_free((void *)s2), "");
	else if (!s1)
		return (gc_free((void *)s1), gc_free((void *)s2), (char *)s2);
	else if (!s2)
		return (gc_free((void *)s1), gc_free((void *)s2), (char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)gc_malloc(sizeof(char) * (len + 1));
	if (!join)
		return (gc_free((void *)s1), gc_free((void *)s2), NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		join[i + j] = s2[j];
	return (gc_free((void *)s1), gc_free((void *)s2), join);
}
