/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:56:45 by fparreir          #+#    #+#             */
/*   Updated: 2024/03/25 17:32:27 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_check_sign(const char *str, int *pos)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i + 1] == 45 || str[i + 1] == 43)
			return (0);
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	*pos = i;
	return (sign);
}

long int	ft_atol(const char *str)
{
	int			sign;
	int			i;
	long int	res;

	i = 0;
	res = 0;
	sign = ft_check_sign(str, &i);
	if (sign == 1 || sign == -1)
	{
		while (str[i] && (str[i] >= 48 && str[i] <= 57))
		{
			res *= 10;
			res += str[i] - 48;
			i++;
			if (i >= 19)
				return (-1);
		}
		return (res * sign);
	}
	return (-1);
}
