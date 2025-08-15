/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putulnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 06:06:28 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/27 20:00:35 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putulnbr(unsigned long long n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += ft_putulnbr(n / 10);
	len += ft_putchar(n % 10 + '0');
	return (len);
}

int	ft_putulnbr_fd(unsigned long long n, int fd)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += ft_putulnbr_fd(n / 10, fd);
	len += ft_putchar_fd(n % 10 + '0', fd);
	return (len);
}
