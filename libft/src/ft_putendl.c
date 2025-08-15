/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:32:56 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/27 19:58:59 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putendl(char *s)
{
	int	len;

	len = ft_strlen(s);
	write(1, s, len);
	len += ft_putchar('\n');
	return (len);
}

int	ft_putendl_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
	len += ft_putchar_fd('\n', fd);
	return (len);
}
