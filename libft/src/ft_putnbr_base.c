/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:41:20 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/27 19:59:54 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr_base(long int nb, int base)
{
	int	len;

	if (base > 36)
		return (0);
	else if (base == 10)
		return (ft_putnbr(nb));
	len = 0;
	if (nb < 0)
	{
		len += write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= base)
	{
		len += ft_putnbr_base(nb / base, base);
		len += ft_putnbr_base(nb % base, base);
	}
	else if (nb <= 9)
		len += ft_putchar(nb + '0');
	else
		len += ft_putchar(nb - 10 + 'a');
	return (len);
}

int	ft_putnbr_base_fd(long int nb, int base, int fd)
{
	int	len;

	if (base > 36)
		return (0);
	else if (base == 10)
		return (ft_putnbr_fd(nb, fd));
	len = 0;
	if (nb < 0)
	{
		len += write(fd, "-", 1);
		nb *= -1;
	}
	if (nb >= base)
	{
		len += ft_putnbr_base_fd(nb / base, base, fd);
		len += ft_putnbr_base_fd(nb % base, base, fd);
	}
	else if (nb <= 9)
		len += ft_putchar_fd(nb + '0', fd);
	else
		len += ft_putchar_fd(nb - 10 + 'a', fd);
	return (len);
}
