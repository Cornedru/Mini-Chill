/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:46:21 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/01 04:13:24 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	else if (nb < 0)
	{
		len += write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		len += ft_putnbr(nb / 10);
	len += ft_putchar(nb % 10 + '0');
	return (len);
}

int	ft_putnbr_fd(int nb, int fd)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		return (write(fd, "-2147483648", 11));
	else if (nb < 0)
	{
		len += write(fd, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		len += ft_putnbr_fd(nb / 10, fd);
	len += ft_putchar_fd(nb % 10 + '0', fd);
	return (len);
}
