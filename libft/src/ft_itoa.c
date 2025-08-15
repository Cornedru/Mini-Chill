/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:26:32 by oligrien          #+#    #+#             */
/*   Updated: 2025/04/29 22:44:47 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	intlen(long int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	ln;
	char		*nbr;
	int			len;

	ln = (long int)n;
	len = intlen(ln);
	nbr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	if (ln == 0)
		nbr[0] = '0';
	if (ln < 0)
	{
		nbr[0] = '-';
		ln *= -1;
	}
	nbr[len] = '\0';
	while (ln > 0)
	{
		nbr[len - 1] = ln % 10 + '0';
		ln /= 10;
		len--;
	}
	return (nbr);
}
