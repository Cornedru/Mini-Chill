/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:46:47 by oligrien          #+#    #+#             */
/*   Updated: 2025/04/29 22:49:57 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_puthex(unsigned long long nb, const char c)
{
	int	len;

	len = 0;
	if (nb >= 16)
	{
		len += ft_puthex(nb / 16, c);
		len += ft_puthex(nb % 16, c);
	}
	else if (nb <= 9)
		len += ft_putchar(nb + '0');
	else
	{
		if (c == 'x')
			len += ft_putchar(nb - 10 + 'a');
		if (c == 'X')
			len += ft_putchar(nb - 10 + 'A');
	}
	return (len);
}

int	conv_p(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		return (ft_putstr("(nil)"));
	len += ft_putstr("0x");
	len += ft_puthex(ptr, 'x');
	return (len);
}

static int	convert(const char *input, va_list *ap)
{
	if (*input == '%')
		return (ft_putchar('%'));
	if (*input == 'c')
		return (ft_putchar(va_arg(*ap, int)));
	if (*input == 's')
		return (ft_putstr(va_arg(*ap, char *)));
	if (*input == 'p')
		return (conv_p((unsigned long long)va_arg(*ap, void *)));
	if (*input == 'd' || *input == 'i')
		return (ft_putnbr(va_arg(*ap, int)));
	if (*input == 'u')
		return (ft_putulnbr(va_arg(*ap, unsigned int)));
	if (*input == 'x' || *input == 'X')
		return (ft_puthex(va_arg(*ap, unsigned int), *input));
	return (0);
}

int	check_conv(const char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '%')
		{
			if (!ft_strchr("cspdiuxX%", input[i + 1])
				&& ft_isalnum(input[i + 1]) && input[i - 1] != '%')
			{
				ft_putstr("error: unknown conversion type character '");
				ft_putchar(input[i + 1]);
				ft_putendl("' in format");
				return (0);
			}
		}
	}
	return (1);
}

int	ft_printf(const char *input, ...)
{
	va_list	*ap;
	int		printlen;

	if (!input)
		return (-1);
	if (!check_conv(input))
		return (0);
	printlen = 0;
	ap = malloc(sizeof(va_list));
	va_start(*ap, input);
	while (*input)
	{
		if (*input == '%')
			printlen += convert(++input, ap);
		else
			printlen += write(1, input, 1);
		input ++;
	}
	va_end(*ap);
	free(ap);
	return (printlen);
}
