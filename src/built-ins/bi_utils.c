/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:52:55 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/09 23:02:41 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	to_number(const char *nptr, int *sign)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static int	is_overflow(unsigned long long d, unsigned long long nb, int sign,
		int *fail)
{
	if (sign == 1)
	{
		if (nb > LLONG_MAX / 10 || (nb == LLONG_MAX / 10 && d > LLONG_MAX % 10))
		{
			if (fail)
				*fail = 1;
			return (1);
		}
	}
	else
	{
		if (nb > ((unsigned long long)LLONG_MAX + 1) / 10
			|| (nb == ((unsigned long long)LLONG_MAX + 1) / 10
				&& d > ((unsigned long long)LLONG_MAX + 1) % 10))
		{
			if (fail)
				*fail = 1;
			return (1);
		}
	}
	return (0);
}

long long int	ft_atoll(const char *nptr, int *fail)
{
	unsigned long long int	nb;
	int						sign;
	int						i;

	if (!nptr)
		return (0);
	if (fail)
		*fail = 0;
	sign = 1;
	i = to_number(nptr, &sign);
	nb = 0;
	while (ft_isdigit(nptr[i]))
	{
		if (is_overflow(nptr[i] - '0', nb, sign, fail))
			return (0);
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	while (nptr[i] == ' ' || nptr[i] == '\t')
		i++;
	if (nptr[i] && fail)
		*fail = 2;
	return (nb * sign);
}

bool	is_valid_env_var_name(const char *name)
{
	int	i;

	if (!name || !*name)
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
