/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:00:41 by fparreir          #+#    #+#             */
/*   Updated: 2023/05/13 14:30:06 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *str, int c, size_t length)
{
	unsigned char	*string;
	unsigned char	value;

	string = (unsigned char *)str;
	value = (unsigned char)c;
	while (length--)
	{
		if (*string == value)
			return ((unsigned char *)string);
		string++;
	}
	return (0);
}
