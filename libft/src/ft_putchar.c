/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:32:56 by oligrien          #+#    #+#             */
/*   Updated: 2025/06/27 19:58:28 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
