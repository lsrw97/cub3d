/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:20:32 by fparreir          #+#    #+#             */
/*   Updated: 2023/05/13 14:29:51 by fparreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*buffer;
	size_t	i;

	i = 0;
	buffer = malloc(nmemb * size);
	if (!buffer)
		return (0);
	while (i < nmemb * size)
		buffer[i++] = 0;
	return (buffer);
}
