/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:11:18 by fparreir          #+#    #+#             */
/*   Updated: 2023/05/13 14:34:33 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t size)
{
	size_t	result;
	size_t	i;

	i = 0;
	result = ft_strlen(src);
	if (size > 0)
	{
		while (*src && i++ < (size - 1))
			*dest++ = (char)*src++;
		*dest = 0;
	}
	return (result);
}
