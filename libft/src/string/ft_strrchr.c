/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:17:46 by fparreir          #+#    #+#             */
/*   Updated: 2023/05/13 14:35:11 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*s;

	s = str;
	while (*str)
		str++;
	while (str >= s)
	{
		if (*str == (char)c)
			return ((char *)str);
		str--;
	}
	return (0);
}
