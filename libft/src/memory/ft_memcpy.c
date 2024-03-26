/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <fparreir@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:01:58 by fparreir          #+#    #+#             */
/*   Updated: 2023/05/13 14:30:22 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t length)
{
	unsigned char	*destiny;
	unsigned char	*source;

	source = (unsigned char *)src;
	destiny = (unsigned char *)dest;
	if (!dest && !src)
		return (dest);
	while (source && *source && length--)
		*destiny++ = *source++;
	return (dest);
}
